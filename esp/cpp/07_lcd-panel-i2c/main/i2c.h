/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#ifndef I2C_H
#define I2C_H

#define I2C_BUS_PORT  0

#include <driver/i2c_master.h>

/**
 * Encapsulates ESP I2C creation and usage.
 */
struct I2C {
  /**
   * Construct and initialize an ESP I2C master bus.
   * An I2C constructor may only be called one time in any application.
   *
   * @param sda GPIO pin number for SDA
   * @param scl GPIO pin number for SCL
   * @param rst GPIO pin number for RST
   */
  I2C(gpio_num_t sda, gpio_num_t scl, int rst = -1) :
      I2C((i2c_master_bus_config_t) {
              .i2c_port = I2C_BUS_PORT,
              .sda_io_num = sda,
              .scl_io_num = scl,
              .clk_source = I2C_CLK_SRC_DEFAULT,
              .glitch_ignore_cnt = 7,
              .flags {
                  .enable_internal_pullup = true,
              },
          },
          rst
      ) { }

  /**
   * Construct an ESP I2C master bus given a specific ESP I2C configuration.
   * An I2C constructor may only be called one time in any application.
   *
   * @param config ESP I2C master bus configuration.
   * @param rst GPIO pin number for RST
   */
  explicit I2C(i2c_master_bus_config_t config, int rst = -1) :
      esp_bus_config_(config),
      rst_num_(rst)
  {
    i2c_master_bus_handle_t i2c;
    ESP_LOGI(TAG, "Initializing new master I2C bus");
    ESP_ERROR_CHECK(i2c_new_master_bus(&esp_bus_config_, &i2c));
  }

  ~I2C() = default;

  //
  // GETTERS

  /**
   * ESP I2C master bus handle getter.
   * This will fail if an I2C instance was never constructed.
   */
  static i2c_master_bus_handle_t get()
  {
    i2c_master_bus_handle_t i2c = nullptr;
    ESP_ERROR_CHECK(i2c_master_get_bus_handle(0, &i2c));
    return i2c;
  }

  //
  // PUBLIC MEMBERS

  /// ESP I2C master bus configuration used during initialization.
  i2c_master_bus_config_t esp_bus_config_;

  /// RST GPIO pin number.
  int rst_num_;

private:

  //
  // PRIVATE MEMBERS

  /// Tag used for ESP logging.
  constexpr static const char *TAG = "I2C";
};

#endif //I2C_H
