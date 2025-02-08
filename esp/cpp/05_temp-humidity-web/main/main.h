#ifndef  MAIN_H
#define  MAIN_H

#include <cstdint>
#include "dht.h"

class DHT {
public:
  DHT(gpio_num_t gpio, dht_sensor_type_t type) :
      gpio_(gpio), type_(type) { }

  ~DHT() = default;

  /**
   * Read temperature from DHT sensor
   *
   * @param f True to return in Fahrenheit, False for Celsius.
   */
  float readTemperature(bool f = true);

  /**
   * Read humidity from DHT sensor.
   */
  float readHumidity();

private:
  gpio_num_t gpio_;
  dht_sensor_type_t type_;

};


#endif // MAIN_H
