/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#ifndef PANEL_H
#define PANEL_H

#include "panel_device.h"

/**
 * Encapsulates esp_lcd_panel handles and operations.
 * The only exception is esp_lcd_panel_io_i2c_config_t owned by IPanelDevice.
 * This structure requires details specific to the implementing device.
 *
 * Panel is an implementation detail of Display, not meant to be used directly.
 */
struct Panel {
  /**
   * Construct a new Panel using an object that implements IPanelDevice.
   *
   * @param device An object that implements the IPanelDevice interface.
   */
  explicit Panel(IPanelDevice &device) :
      device_(&device),
      esp_io_(nullptr),
      esp_panel_(nullptr),
      esp_panel_config_(
          (esp_lcd_panel_dev_config_t) {
              .reset_gpio_num = device_->rst_num_,
              .bits_per_pixel = 1,
              .vendor_config = device_->vendor_config(),
          }
      )
  {
    esp_io_ = device_->create_io_handle();

    device_->create_panel(esp_panel_config_, esp_io_, esp_panel_);

    ESP_LOGI(TAG, "Resetting panel display");
    ESP_ERROR_CHECK(esp_lcd_panel_reset(esp_panel_));
    ESP_LOGI(TAG, "Initializing panel display");
    ESP_ERROR_CHECK(esp_lcd_panel_init(esp_panel_));
    ESP_LOGI(TAG, "Turning on panel display");
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(esp_panel_, true));
  }

  ~Panel() = default;

  //
  // PUBLIC MEMBERS

  /// Pointer to object using known interface for IPanelDevice.
  IPanelDevice *device_;

  /// ESP LCD panel IO handle.
  esp_lcd_panel_io_handle_t esp_io_;

  /// ESP LCD panel handle.
  esp_lcd_panel_handle_t esp_panel_;

  /// ESP LCD panel configuration structure.
  esp_lcd_panel_dev_config_t esp_panel_config_;

  /**
   * Registers LVGL draw buffers and callbacks for rendering the display.
   *
   * @param display_handle Pointer to the LVGL display to use for rendering.
   */
  inline void register_display_callbacks(lv_display_t *display_handle) const
  {
    device_->register_rendering_data(display_handle, esp_io_);
    device_->register_lvgl_tick_timer();
  }

private:

  //
  // PRIVATE MEMBERS

  /// Tag used for ESP logging.
  constexpr static const char *TAG = "Panel";
};

#endif //PANEL_H
