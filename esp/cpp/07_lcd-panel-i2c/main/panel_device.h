/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#ifndef PANEL_DEVICE_H
#define PANEL_DEVICE_H

#include <esp_lcd_panel_dev.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_io.h>
#include <esp_log.h>

#include <display/lv_display.h>

#include "i2c.h"

// LVGL reserves 2x4 bytes in the buffer to be used as a palette.
// This additional space must be added to the IPanelDevice::buf_size_.
#define LVGL_PALETTE_SIZE      8
#define LVGL_TICK_PERIOD_MS    5
#define LVGL_TASK_STACK_SIZE   (4 * 1024)
#define LVGL_TASK_PRIORITY     2

#define LCD_H_RES              128
#define LCD_V_RES              64

/**
 * Wraps some foundational operations performed on pixel coordinates when
 * dealing with pointer arithmetic. Most of these could be done ad-hoc as needed
 * but using this helper reduces the risk of errors.
 */
struct Pixel {
  /**
   * Calculate byte offset for the pixel at [x,y] within a horizontally-mapped
   * monochrome uint8 draw buffer, using the initialized horizontal resolution.
   *
   * We use `>> 3` because each pixel requires 1 bit, but each uint8 in the draw
   * buffer can hold 8 bits. To find the uint8 value in our draw buffer that
   * stores this pixel's value we must compensate for this when using pixel
   * coordinates in byte math.
   *
   * Therefore, each uint8 in the draw buffer stores the state of 8 pixels.
   * Below is an example of calculating for [x, y] pixel coordinates [20, 10].
   * The example uses a horizontal resolution of 128.
   *
   * For the horizontal case, each row (y) of the image is represented by
   * `hor_res >> 3` bytes (16). The byte-offset of the first pixel in the 10th
   * row for example is `16 * 10` = 160.
   *
   * Since the pixels are stored horizontally we must calculate the 20th pixel
   * column (x) as `160 + (20 >> 3)`, or `160 + (20 / 8)` to get a final offset
   * of 162.
   *
   * @param x X pixel coordinate to find byte offset.
   * @param y Y pixel coordinate to find byte offset.
   * @param hor_res horizontal resolution of the display.
   * @return byte offset for a single-byte monochrome pixel at [x,y].
   */
  [[maybe_unused]] [[nodiscard]] static ptrdiff_t
  horizontal_byte_offset(const int32_t &x, const int32_t &y,
                         const int32_t &hor_res = LCD_V_RES)
  {
    // Convert pixel (bit) coordinates to byte coordinates in the draw buffer.
    return (hor_res >> 3) * y + (x >> 3);
  }

  /**
   * Calculate byte offset for the pixel at [x,y] within a vertically-mapped
   * monochrome uint8 draw buffer, using the initialized horizontal resolution.
   *
   * We use `>> 3` because each pixel requires 1 bit, but each uint8 in the draw
   * buffer can hold 8 bits. To find the uint8 value in our draw buffer that
   * stores this pixel's value we must compensate for this when using pixel
   * coordinates in byte math.
   *
   * Therefore, each uint8 in the draw buffer stores the state of 8 pixels.
   * Below is an example of calculating for [x, y] pixel coordinates [20, 10].
   * The example uses a horizontal resolution of 128.
   *
   * For the vertical case, each row (y) of the image is represented by
   * `hor_res` bytes (128) - one for each column (x). Because the pixels are
   * stored vertically, the byte-offset of the first pixel in the 10th row is
   * `128 * (10 >> 3)` or * `128 * (10 / 8)` = 128.
   *
   * From this location we can simply calculate the 20th pixel column (x) as
   * `128 + 20` to get a final offset of 148, because the pixels are stored in a
   * columnar format.
   *
   * @param x X pixel coordinate to find byte offset.
   * @param y Y pixel coordinate to find byte offset.
   * @param hor_res horizontal resolution of the display.
   * @return byte offset for a single-byte monochrome pixel at [x,y].
   */
  [[maybe_unused]] [[nodiscard]] static ptrdiff_t
  vertical_byte_offset(const int32_t &x, const int32_t &y,
                       const int32_t &hor_res = LCD_V_RES)
  {
    // Convert pixel (bit) coordinates to byte coordinates in the draw buffer.
    return hor_res * (y >> 3) + x;
  }

  /**
   * Finds the Most Significant Bit location of bit `i` in a byte.
   *
   *          MSB           LSB
   * bits      7 6 5 4 3 2 1 0
   * data      8 7 6 5 4 3 2 1
   *          Left         Right
   *
   * @return bitmask for MSB location of `i`.
   */
  [[maybe_unused]] [[nodiscard]] static uint8_t
  msb_mask(const int32_t &i) { return 1 << (7 - i % 8); }

  /**
   * Finds the Least Significant Bit location of bit `i` in a byte.
   *
   *          LSB           MSB
   * bits      0 1 2 3 4 5 6 7
   * data      1 2 3 4 5 6 7 8
   *          Left         Right
   *
   * @return bitmask for LSB location of `i`.
   */
  [[maybe_unused]] [[nodiscard]] static uint8_t
  lsb_mask(const int32_t &i) { return 1 << (i % 8); }
};


/**
 * Encapsulates vendor specific ESP LCD panel initialization logic.
 * This pure virtual interface can be inherited from for using new LCD devices.
 * See SSD1306 as an example to implement IPanelDevice for NT35510 or ST7789.
 *
 * At this time only I2C is supported.
 * Classes that inherit from this interface should likely be marked final.
 */
class IPanelDevice {
public:
  /**
   * Construct an IPanelDevice.
   *
   * @param i2c I2C object. Eventually this will mature to IProtocol or similar.
   * @param config I2C configuration for this device.
   * @param height Height of the device screen in pixels.
   * @param width Width of the device screen in pixels.
   */
  explicit IPanelDevice(I2C &i2c,
                        esp_lcd_panel_io_i2c_config_t config,
                        int width,
                        int height) :
      IPanelDevice(i2c, config, width, height,
                   width * height / 8 + LVGL_PALETTE_SIZE) { }

  /**
   * Construct an IPanelDevice.
   *
   * @param i2c I2C object. Eventually this will mature to IProtocol or similar.
   * @param config I2C configuration for this device.
   * @param height Height of the device screen in pixels.
   * @param width Width of the device screen in pixels.
   * @param draw_buf_size Size of the draw buffer for this device.
   */
  explicit IPanelDevice(I2C &i2c,
                        esp_lcd_panel_io_i2c_config_t io_config,
                        int width,
                        int height,
                        size_t draw_buf_size) :
      width_(width),
      height_(height),
      rst_num_(i2c.rst_num_),
      lv_buf_size_(draw_buf_size),
      esp_io_config_(io_config),
      lv_buf_(nullptr) { }

  virtual ~IPanelDevice() = default;

  //
  // PUBLIC METHODS

  /**
   * Create an LVGL display using the width and height of this device.
   *
   * @return Handle to the created LVGL display.
   */
  [[nodiscard]] lv_display_t *create_display() const
  {
    auto display = lv_display_create(width_, height_);
    assert(display);
    return display;
  }

  /**
   * Create an ESP LCD panel IO handle.
   *
   * @return The created ESP LCD panel IO handle.
   */
  [[nodiscard]] esp_lcd_panel_io_handle_t create_io_handle()
  {
    ESP_LOGI(TAG, "Creating panel IO handle");
    esp_lcd_panel_io_handle_t handle = nullptr;
    ESP_ERROR_CHECK(
        esp_lcd_new_panel_io_i2c(I2C::get(), &esp_io_config_, &handle));
    return handle;
  }

  /**
   * Create and initialize an ESP panel handle.
   * IPanelDevice implementors must initialize the panel within init_panel.
   *
   * @param config ESP LCD panel configuration.
   * @param io ESP LCD panel IO handle.
   * @param [out] panel ESP LCD panel handle output pointer location.
   */
  void create_panel(esp_lcd_panel_dev_config_t &config,
                    esp_lcd_panel_io_handle_t io,
                    esp_lcd_panel_handle_t &panel)
  {
    // If the passed handle is already allocated, delete it.
    if (panel != nullptr) {
      ESP_LOGI(TAG, "Removing unused panel");
      esp_lcd_panel_del(panel);
    }

    ESP_LOGI(TAG, "Installing vendor panel driver");
    // Call pure virtual method responsible for initializing the panel handle.
    init_panel(config, io, panel);
  }

  /**
   * Retrieve the device specific vendor configuration structure.
   *
   * @return Address of vendor configuration structure.
   * @sa SSD1306::vendor_config
   */
  virtual void *vendor_config() = 0;

  /**
   * Registers LVGL draw buffers and callbacks for this display.
   *
   * An implementation of the interface can optionally override this method to
   * provide custom LVGL callbacks and display configurations.
   *
   * @param display_handle LVGL display handle to use for rendering.
   * @param io_handle IO handle for the ESP LCD panel.
   */
  virtual void register_rendering_data(lv_display_t *display_handle,
                                       esp_lcd_panel_io_handle_t io_handle);

  /**
   * Registers LVGL ticker timer callback for rendering this display.
   *
   * An implementation of the interface can optionally override this method to
   * provide custom LVGL callbacks and tick configurations.
   */
  virtual void register_lvgl_tick_timer();

  //
  // PUBLIC MEMBERS

  /// Width of the device screen in pixels.
  int32_t width_;

  /// Height of the device screen in pixels.
  int32_t height_;

  /// RST GPIO pin number.
  int rst_num_;

  /// LVGL draw buffer size for the device.
  size_t lv_buf_size_;

  /// ESP LCD panel IO configuration.
  esp_lcd_panel_io_i2c_config_t esp_io_config_;

protected:
  /**
   * Static accessor to a static buffer to store draw buffer data for the panel.
   *
   * This method is protected to allow an implementation to provide a custom
   * callback method similar to IPanelDevice::lvgl_flush_cb.
   *
   * The buffer is allocated statically within the scope of this function to
   * allow creating multiple panels that _each_ manage their own statically
   * allocated draw buffer data. This simplifies implementing the interface by
   * taking this responsibility off of the implementor. The buffer will only be
   * allocated if this method is called, so the memory is only used if required.
   *
   * @return Pointer to uint8 draw buffer data.
   * @sa register_rendering_data for overriding LVGL rendering callbacks.
   */
  static uint8_t *get_additional_draw_buffer()
  {
    // Static to the scope of this function, not the compilation unit.
    // For LV_COLOR_FORMAT_I1 we need an extra buffer to hold converted data.
    static uint8_t oled_buffer[LCD_H_RES * LCD_V_RES / 8];
    return oled_buffer;
  }

private:

  //
  // PRIVATE METHODS

  /**
    * Initializes the ESP panel using vendor specific APIs and configurations.
    * This method should implement any setup logic specific to the device.
    *
    * @param config ESP LCD panel configuration.
    * @param io ESP LCD panel IO handle.
    * @param [out] panel ESP LCD panel handle output pointer location.
    */
  virtual void init_panel(esp_lcd_panel_dev_config_t &config,
                          esp_lcd_panel_io_handle_t io,
                          esp_lcd_panel_handle_t &panel) = 0;

  //
  // PRIVATE STATIC METHODS

/**
 * The callback invoked when panel IO finishes transferring color data.
 * This signals that the panel is ready to flush image data to the display.
 *
 * @param panel LCD panel IO handles.
 * @param data Panel IO event data, fed by driver.
 * @param user_ctx User data, passed from `esp_lcd_panel_io_xxx_config_t`.
 * @return Whether a high priority task has been waken up by this function.
 * @sa SSD1306::SSD1306 for setting user_ctx data passed to the callback.
 * @sa register_rendering_data for overriding this callback.
 */
  static bool lvgl_flush_ready_cb(esp_lcd_panel_io_handle_t panel,
                                  esp_lcd_panel_io_event_data_t *data,
                                  void *user_ctx);

  /**
   * The callback invoked for flushing the rendered image to the display.
   *
   * `px_map` contains the rendered image as raw pixel map and it should be
   *  copied to `area` on the display.
   *
   * The following details are crucial for understanding the logic surrounding
   * flushing to the display in this example.
   *
   * The order of bits within the px_map from _LVGL_ is MSB first.
   *              MSB           LSB
   *     bits      7 6 5 4 3 2 1 0
   *     pixels    0 1 2 3 4 5 6 7
   *              Left         Right
   *
   * The bytes from _LVGL_ are mapped to pixel rows of the display
   * 8 bits (pixels) per byte -
   * [0, 0, 0, 0, 0, 0, 0, 0]
   * [0, 0, 0, 0, 0, 0, 0, 0]
   * [0, 0, 0, 0, 0, 0, 0, 0]
   *
   * The order of bits expected by the _display driver_ is LSB first.
   * We must preserve pairing of each bit and pixel when writing to the display.
   *              LSB           MSB
   *     bits      0 1 2 3 4 5 6 7
   *     pixels    7 6 5 4 3 2 1 0
   *              Left         Right
   *
   * Bytes expected by the _display driver_ map to pixel columns of the display.
   * 8 bits (pixels) per byte -
   * [0, [0, [0, [0,
   *  0,  0,  0,  0,
   *  0,  0,  0,  0,
   *  0,  0,  0,  0,
   *  0,  0,  0,  0,
   *  0,  0,  0,  0,
   *  0,  0,  0,  0,
   *  0]  0]  0]  0]
   *
   * These layouts in memory have no opinion on the shape of the image. The
   * beginning and end of a row or a column for example is entirely dependent
   * on how the data is accessed. The vertical and horitzontal resolution may
   * vary between displays.
   *
   * For the LV_COLOR_FORMAT_I1 color format we are using, an additional buffer
   * is needed for transposing the bits to the vertical arrangement required by
   * the display driver that is outlined above.
   *
   * This callback implementation is an example of handling this transposition
   * and flushing the data to the display in the expected format.
   *
   * @param display LVGL display handle to use for rendering.
   * @param area Area of the display being flushed.
   * @param px_map Rendered image data for writing to the display area.
   * @sa register_rendering_data for overriding this callback.
   * @sa get_additional_draw_buffer
   */
  static void lvgl_flush_cb(lv_display_t *display,
                            const lv_area_t *area,
                            uint8_t *px_map);

  /**
   * Callback invoked for every period of the timer.
   *
   * This callback _must_ call lv_tick_inc to inform LVGL how much time has
   * elapsed since the last period of the timer.
   *
   * @param data User data passed to the callback.
   * @sa register_lvgl_tick_timer for setting user data and the tick period of
   *        the timer, or overriding this callback entirely.
   */
  static void lvgl_increase_tick_cb(void *data);

  /**
   * FreeRTOS task callback invoked for handling LVGL events or updating the UI.
   *
   * This function is intentionally an endless loop and should never return.
   * LVGL initialization logic can optionally be added before entering the loop.
   * Input logic can optionally be handled within the loop.
   *
   * This callback _must_ call lv_timer_handler to handle LVGL periodic timers.
   *
   * @param data User data passed to the callback.
   * @sa register_lvgl_tick_timer for overriding this callback.
   */
  [[noreturn]] static void lvgl_port_task(void *data);

  //
  // PRIVATE MEMBERS

  /// LVGL draw buffer associated with this Display's lv_display_t.
  void *lv_buf_;

  /// Tag used for ESP logging.
  constexpr static const char *TAG = "IPanelDevice";
};

#endif // PANEL_DEVICE_H
