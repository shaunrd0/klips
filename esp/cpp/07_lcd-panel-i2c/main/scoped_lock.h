/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#ifndef SCOPED_LOCK_H
#define SCOPED_LOCK_H

#include <mutex>

/**
 * Obtains LVGL API mutex lock for the duration of local scope.
 *
 * LVGL library is not thread-safe, this lock should be held when making calls
 * to the LVGL API, and released as soon as possible when finished.
 */
struct ScopedLock {
  explicit ScopedLock() { _lock_acquire(&lv_lock_); }

  ~ScopedLock() { _lock_release(&lv_lock_); }

  /// Mutex used to protect LVGL API calls.
  static _lock_t lv_lock_;
};

#endif // SCOPED_LOCK_H
