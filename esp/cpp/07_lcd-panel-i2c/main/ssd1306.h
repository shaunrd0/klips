/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#ifndef SSD1306_H
#define SSD1306_H

#include <esp_lcd_panel_ssd1306.h>

#include "panel_device.h"

// According to specific display hardware.
// https://www.digikey.com/en/products/detail/winstar-display/WEA012864DWPP3N00003/20533255
#define SCREEN_WIDTH           128  // OLED display width, in pixels.
#define SCREEN_HEIGHT          64  // OLED display height, in pixels.

// According to SSD1306 datasheet.
// https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
#define I2C_HW_ADDR            0x3C
#define LCD_PIXEL_CLOCK_HZ     (400 * 1000)
// Bit number used to represent command and parameter
#define LCD_CMD_BITS           8
#define LCD_PARAM_BITS         8

/**
 * Example of implementing the IPanelDevice interface for SSD1306 LCD device.
 */
class SSD1306 final : public IPanelDevice {
public:
  /**
   * Construct a new SSD1306 device.
   *
   * @param i2c I2C master bus to manage this device.
   */
  explicit SSD1306(I2C &i2c) :
      SSD1306(i2c, {.height = SCREEN_HEIGHT}) { }

  /**
   * Construct a new SSD1306 device given a specific SSD1306 configuration.
   *
   * @param i2c I2C master bus to manage this device.
   * @param config SSD1306 vendor configuration.
   * @param width Width of the device screen in pixels.
   * @param height Height of the device screen in pixels.
   */
  SSD1306(I2C &i2c,
          esp_lcd_panel_ssd1306_config_t config,
          int width = SCREEN_WIDTH,
          int height = SCREEN_HEIGHT
  ) :
      IPanelDevice(i2c,
                   (esp_lcd_panel_io_i2c_config_t) {
                       .dev_addr = I2C_HW_ADDR,
                       // User data to pass to the LVGL flush_ready callback.
                       // See IPanelDevice::lvgl_flush_ready_cb
                       .user_ctx = nullptr,
                       .control_phase_bytes = 1,
                       .dc_bit_offset = 6,
                       .lcd_cmd_bits = LCD_CMD_BITS,
                       .lcd_param_bits = LCD_PARAM_BITS,
                       .scl_speed_hz = LCD_PIXEL_CLOCK_HZ,
                   },
                   width,
                   height
      ),
      ssd1306_config_(config) { }

  ~SSD1306() final = default;

  //
  // PUBLIC METHODS

  /**
   * Provides the SSD1306 vendor configuration to IPanelDevice consumers.
   *
   * @return Address of the SSD1306 vendor configuration structure.
   */
  void *vendor_config() override
  {
    return &ssd1306_config_;
  }

  //
  // PUBLIC MEMBERS

  /// SSD1306 configuration structure.
  esp_lcd_panel_ssd1306_config_t ssd1306_config_;

private:

  //
  // PRIVATE METHODS

  /// Initializes the ESP LCD panel handle for the SSD1306 device.
  void init_panel(esp_lcd_panel_dev_config_t &config,
                  esp_lcd_panel_io_handle_t io,
                  esp_lcd_panel_handle_t &panel) override
  {
    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io, &config, &panel));
  }
};

#endif // SSD1306_H
