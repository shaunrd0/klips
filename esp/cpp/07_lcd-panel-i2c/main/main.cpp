/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#include "display.h"
#include "ssd1306.h"

// Pin may vary based on your schematic.
#define PIN_SDA                GPIO_NUM_21
#define PIN_SCL                GPIO_NUM_22
#define PIN_RST                (-1)

I2C i2c(PIN_SDA, PIN_SCL, PIN_RST);

void setup()
{
  SSD1306 ssd1306(i2c);
  Display d(ssd1306);

  d.set_text("Test test 12345678910",
             "test-text1",
             LV_LABEL_LONG_SCROLL,
             LV_ALIGN_CENTER);

  d.set_text("Test test changing text",
             "test-text1",
             LV_LABEL_LONG_SCROLL,
             LV_ALIGN_CENTER);

  d.set_text("Hello hello hello hello hello hello hello hello!", "test-text2");

  d.set_text("A random sentence with no meaning at all.",
             "test-text3",
             LV_LABEL_LONG_CLIP,
             LV_ALIGN_BOTTOM_MID);
}

void loop() { }
