/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#include <lv_init.h>

#include "display.h"

// Static TimeKeeper for managing ESP timers across all displays.
TimeKeeper Display::timers_;

Display::Display(IPanelDevice &device) :
    panel_(device)
{
  if (!lv_is_initialized()) {
    ESP_LOGI(TAG, "Initialize LVGL");
    lv_init();
  }

  ESP_LOGI(TAG, "Creating LVGL display");
  lv_display_ = panel_.device_->create_display();
  // associate the i2c panel handle to the display
  lv_display_set_user_data(lv_display_, panel_.esp_panel_);

  panel_.register_display_callbacks(lv_display_);
}

void Display::set_text(const char *text,
                       const char *name,
                       lv_label_long_mode_t long_mode,
                       lv_align_t align)
{
  // Lock the mutex due to the LVGL APIs are not thread-safe.
  ScopedLock lock;

  ESP_LOGI(TAG, "Display LVGL Scroll Text");
  lv_obj_t *scr = lv_display_get_screen_active(lv_display_);

  // Create the label if it's `name` doesn't already exist in the map keys.
  if (!lv_objects_.count(name)) {
    lv_objects_[name] = lv_label_create(scr);
  }
  auto obj = lv_objects_[name];

  // Set text and long mode.
  lv_label_set_long_mode(obj, long_mode);
  lv_label_set_text(obj, text);

  // Set the size of the screen.
  // If you use rotation 90 or 270 use lv_display_get_vertical_resolution.
  lv_obj_set_width(obj, lv_display_get_horizontal_resolution(lv_display_));
  lv_obj_align(obj, align, 0, 0);
}
