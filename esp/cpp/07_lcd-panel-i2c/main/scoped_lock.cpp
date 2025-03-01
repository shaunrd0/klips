/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com                     ##
##############################################################################
*/
#include "scoped_lock.h"

// LVGL library is not thread-safe, this example calls LVGL APIs from tasks.
// We must use a mutex to protect it.
_lock_t ScopedLock::lv_lock_;
