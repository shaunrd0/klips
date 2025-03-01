/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#ifndef TIME_KEEPER_H
#define TIME_KEEPER_H

#include <esp_log.h>
#include <esp_timer.h>

#include "i2c.h"

/**
 * Stores arguments and ESP timer handle for a Timer.
 * In general Timers should be used via the TimeKeeper interface only.
 *
 * Timers cannot be copied, and are only created by a TimeKeeper instance.
 * The TimeKeeper can delete existing Timers, calling it's destructor.
 * The ESP timer will be deleted when this class desctructor is called.
 */
struct Timer {
  explicit Timer(esp_timer_create_args_t args) :
      args_(args), esp_timer_(nullptr)
  {
    ESP_LOGI(TAG, "Creating esp_timer with name: '%s'", args_.name);
    ESP_ERROR_CHECK(esp_timer_create(&args, &esp_timer_));
  }

  ~Timer()
  {
    ESP_LOGI(TAG, "Destroying esp_timer with name: '%s'", args_.name);
    ESP_ERROR_CHECK(esp_timer_delete(esp_timer_));
  }

  Timer(const Timer &) = delete;

  Timer(Timer &) = delete;

  Timer &operator=(Timer &) = delete;

  //
  // PUBLIC MEMBERS

  /// Arguments passed to ESP API during timer creation.
  esp_timer_create_args_t args_;

  /// ESP timer handle.
  esp_timer_handle_t esp_timer_;

private:

  //
  // PRIVATE MEMBERS

  /// Tag used for ESP logging.
  constexpr static const char *TAG = "Timer";
};

/**
 * ESP timer mananger class.
 *
 * Timers should only be accessed using the get_handle method.
 * If the Timer destructor is called the underlying ESP timer will be deleted.
 */
struct TimeKeeper {
  /// Timer handle type used for referring to Timers.
  using TimerHandle = Timer *;

  //
  // GETTERS

  TimerHandle get_handle(const char *name)
  {
    return &managed_timers_.at(name);
  }

  TimerHandle operator[](const char *name) { return get_handle(name); }

  //
  // PUBLIC METHODS

  /**
   * Create a new managed Timer with the provided ESP arguments.
   * The timer can be retrieved later using the args.name field value.
   *
   * @param args ESP timer creation arguments.
   * @return TimerHandle Handle to a Timer managed by this TimeKeeper.
   * @sa get_handle
   * @sa operator[](const char*)
   */
  [[maybe_unused]] TimerHandle create_timer(esp_timer_create_args_t args)
  {
    auto rt = managed_timers_.emplace(args.name, args);
    if (!rt.second) {
      ESP_LOGE(TAG, "Timer already exists with name '%s'", args.name);
      return nullptr;
    }
    return &rt.first->second;
  }

  /// Stop a Timer with the given name.
  [[maybe_unused]] void stop_timer(const char *name)
  {
    ESP_ERROR_CHECK(esp_timer_stop(get_handle(name)->esp_timer_));
  }

  /// Delete a Timer with the given name.
  [[maybe_unused]] void delete_timer(const char *name)
  {
    if (managed_timers_.erase(name) == 0) {
      ESP_LOGE(TAG, "Attempt to delete timer that does not exist: '%s'", name);
    }
  }

  /// Create a Timer with the ESP args and call esp_timer_start_periodic.
  [[maybe_unused]] void
  start_new_timer_periodic(esp_timer_create_args_t args,
                           uint64_t period)
  {
    start_timer_periodic(create_timer(args)->args_.name, period);
  }

  /// Calls esp_timer_start_periodic on the Timer with the given name.
  [[maybe_unused]] void start_timer_periodic(const char *name,
                                             uint64_t period)
  {
    ESP_ERROR_CHECK(
        esp_timer_start_periodic(get_handle(name)->esp_timer_, period));
  }

  /// Create a Timer with the ESP args and call esp_timer_start_once.
  [[maybe_unused]] void start_new_timer_once(esp_timer_create_args_t args,
                                             uint64_t timeout_us)
  {
    start_timer_once(create_timer(args)->args_.name, timeout_us);
  }

  /// Calls esp_timer_start_once on the Timer with the given name.
  [[maybe_unused]] void start_timer_once(const char *name,
                                         uint64_t timeout_us)
  {
    ESP_ERROR_CHECK(
        esp_timer_start_once(get_handle(name)->esp_timer_, timeout_us));
  }

private:

  //
  // PRIVATE MEMBERS

  /// Existing ESP timers created for this TimeKeeper instance.
  std::unordered_map<const char *, Timer> managed_timers_;

  /// Tag used for ESP logging.
  constexpr static const char *TAG = "TimeKeeper";
};

#endif // TIME_KEEPER_H
