/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#ifndef DISPLAY_H
#define DISPLAY_H

#include <widgets/label/lv_label.h>

#include <unordered_map>

#include "time_keeper.h"
#include "panel.h"
#include "scoped_lock.h"

/**
 * Encapsulates lv_display handle and related LVGL operations.
 * Contains helper methods that wrap basic LVGL operations such as drawing text.
 * The underlying lv_display can be obtained for manual LVGL operations.
 * @sa ScopedLock
 * @sa Display::get()
 */
class Display {
public:
  /**
   * Construct a new Display using an object that implements IPanelDevice.
   *
   * @param device An object that implements the IPanelDevice interface.
   */
  explicit Display(IPanelDevice &device);

  ~Display() = default;

  Display(const Display &) = delete;

  Display(Display &) = delete;

  Display &operator=(Display &) = delete;

  using lv_display_handle_t = lv_display_t *;

  //
  // GETTERS

  /**
   * Getter for accessing LVGL display handle.
   *
   * @sa ScopedLock for calling custom LVGL API's not implemented by Display.
   */
  [[nodiscard]] inline lv_display_handle_t get() const { return lv_display_; }

  /**
   * Getter for accessing LVGL display handle.
   *
   * @sa ScopedLock for calling custom LVGL API's not implemented by Display.
   */
  [[nodiscard]] inline lv_display_handle_t get() { return lv_display_; }

  /// Dereference operator for accessing LVGL display handle.
  [[nodiscard]] inline lv_display_handle_t operator*() const { return get(); }

  /// Dereference operator for accessing LVGL display handle.
  [[nodiscard]] inline lv_display_handle_t operator*() { return get(); }

  //
  // LVGL OPERATIONS

  /**
   * Create a LVGL label with some given text on the current display.
   * The name of the object can be reused to change text on this label later.
   *
   * @param text Text to write to the display.
   * @param name Name for the LVGL label object associated with this text.
   * @param long_mode LVGL long mode for text wider than the current display.
   * @param align LVGL alignment to use for placing the label on the display.
   */
  void set_text(const char *text,
                const char *name,
                lv_label_long_mode_t long_mode = LV_LABEL_LONG_SCROLL_CIRCULAR,
                lv_align_t align = LV_ALIGN_TOP_MID);

  //
  // PUBLIC STATIC MEMBERS

  /// Public static TimeKeeper for managing ESP timers across all displays.
  static TimeKeeper timers_;

private:

  //
  // PRIVATE MEMBERS

  /// Panel associated with this Display.
  Panel panel_;

  /// LVGL display handle.
  lv_display_handle_t lv_display_;

  /**
   * LVGL object handles stored in the LVGL screen associated with this Display.
   *
   * @sa Display::set_text
   * @sa lv_display_get_screen_active
   */
  std::unordered_map<const char *, lv_obj_t *> lv_objects_;

  /// Tag used for ESP logging.
  constexpr static const char *TAG = "Display";
};

#endif // DISPLAY_H
