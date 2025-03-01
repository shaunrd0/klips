/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#include "panel_device.h"
#include "display.h"

bool IPanelDevice::lvgl_flush_ready_cb(esp_lcd_panel_io_handle_t,
                                       esp_lcd_panel_io_event_data_t *,
                                       void *user_ctx)
{
  auto *disp = (lv_display_t *) user_ctx;
  lv_display_flush_ready(disp);
  return false;
}

void IPanelDevice::lvgl_flush_cb(lv_display_t *display, const lv_area_t *area,
                                 uint8_t *px_map) // NOLINT(*-non-const-parameter)
{
  auto panel_handle =
      (esp_lcd_panel_handle_t) lv_display_get_user_data(display);

  // Necessary because LVGL reserves 2x4 bytes in the buffer for a palette.
  // Since we are monochrome, we don't need these additional bytes.
  // For more information about the monochrome, please refer to:
  // https://docs.lvgl.io/9.2/porting/display.html#monochrome-displays
  // Skip the palette here.
  px_map += LVGL_PALETTE_SIZE;

  uint16_t hor_res = lv_display_get_physical_horizontal_resolution(display);
  int32_t x1 = area->x1;
  int32_t x2 = area->x2;
  int32_t y1 = area->y1;
  int32_t y2 = area->y2;


  // As of 03/01/2025 master branch of LVGL contains this helper for the same.
  // https://docs.lvgl.io/master/API/draw/sw/lv_draw_sw_utils.html
  // lv_draw_sw_i1_convert_to_vtiled()
  for (int32_t y = y1; y <= y2; y++) {
    for (int32_t x = x1; x <= x2; x++) {
      // Get the byte offset of the pixel coordinates using horizontal-mapping.
      int h_offset = Pixel::horizontal_byte_offset(x, y, hor_res);
      // True if the pixel is lit, else false.
      bool chroma_color = px_map[h_offset] & Pixel::msb_mask(x);

      // We need an additional buffer for transposing the pixel data to the
      // vertical format required by the display driver.
      uint8_t *buf = IPanelDevice::get_additional_draw_buffer();
      // Move to the position in the auxillary buffer where the pixel is stored.
      buf += Pixel::vertical_byte_offset(x, y, hor_res);

      // Write the single bit to the monochrome display mapped vertically.
      // Take the Least Significant Bit mask of the Y coordinate to select the
      // bit representing a pixel at position y in a vertically-mapped display.
      if (chroma_color) {
        // Set the vertically-mapped pixel to on.
        *buf &= ~Pixel::lsb_mask(y);
      } else {
        // Set the vertically-mapped pixel to off.
        *buf |= Pixel::lsb_mask(y);
      }
    }
  }
  // Pass the draw buffer to the driver.
  ESP_ERROR_CHECK(
      esp_lcd_panel_draw_bitmap(panel_handle, x1, y1, x2 + 1, y2 + 1,
                                IPanelDevice::get_additional_draw_buffer()));
}

void IPanelDevice::lvgl_increase_tick_cb(void *)
{
  // Tell LVGL how many milliseconds has elapsed
  lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

[[noreturn]] void IPanelDevice::lvgl_port_task(void *)
{
  // Optionally initialize some LVGL objects here before entering loop below.

  ESP_LOGI(TAG, "Starting LVGL task");
  for (uint32_t time_to_next_ms = 0; true; usleep(1000 * time_to_next_ms)) {
    // Obtain LVGL API lock before calling any LVGL methods.
    ScopedLock lock;

    // Optionally handle LVGL input or event logic here.

    // Update LVGL periodic timers.
    time_to_next_ms = lv_timer_handler();
  }
}

void IPanelDevice::register_rendering_data(lv_display_t *display_handle,
                                           esp_lcd_panel_io_handle_t io_handle)
{
  // Create draw buffer.
  ESP_LOGI(TAG, "Allocate separate LVGL draw buffers");
  lv_buf_ = heap_caps_calloc(1, lv_buf_size_,
                             MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  assert(lv_buf_);

  ESP_LOGI(TAG, "Set LVGL draw buffers");
  // Color format must be set first, LVGL9 suooprt new monochromatic format.
  lv_display_set_color_format(display_handle, LV_COLOR_FORMAT_I1);
  lv_display_set_buffers(display_handle, lv_buf_, nullptr,
                         lv_buf_size_,
                         LV_DISPLAY_RENDER_MODE_FULL);
  lv_display_set_rotation(display_handle, LV_DISPLAY_ROTATION_0);

  ESP_LOGI(TAG, "Set LVGL callback for flushing to the display");
  lv_display_set_flush_cb(display_handle, IPanelDevice::lvgl_flush_cb);

  ESP_LOGI(TAG, "Register io panel callback for LVGL flush ready notification");
  const esp_lcd_panel_io_callbacks_t cbs = {
      .on_color_trans_done = IPanelDevice::lvgl_flush_ready_cb,
  };
  ESP_ERROR_CHECK(
      esp_lcd_panel_io_register_event_callbacks(io_handle, &cbs,
                                                display_handle));
}

void IPanelDevice::register_lvgl_tick_timer()
{
  ESP_LOGI(TAG, "Use esp_timer to increase LVGL tick");
  const esp_timer_create_args_t esp_timer_args = {
      .callback = &IPanelDevice::lvgl_increase_tick_cb,
      // Data to pass to the IPanelDevice::lvgl_port_task callback.
      .arg = nullptr,
      .name = "lvgl_tick",
  };
  Display::timers_.start_new_timer_periodic(esp_timer_args,
                                            LVGL_TICK_PERIOD_MS * 1000);

  // LVGL requires a FreeRTOS task for running it's event loop.
  // The lvgl_port_task callback can update the UI or handle input logic.
  // For this basic example we don't do either of these things.
  ESP_LOGI(TAG, "Create LVGL FreeRTOS task");
  // Optionally set user data to pass to LVGL's FreeRTOS task callback here.
  void *user_data = nullptr;
  xTaskCreate(lvgl_port_task, "LVGL", LVGL_TASK_STACK_SIZE,
              user_data, LVGL_TASK_PRIORITY, nullptr);
}
