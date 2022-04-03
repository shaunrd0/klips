/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of condition_variables in multithreaded C++              ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static std::mutex mtx;
std::condition_variable cv;
bool processing = false;

// Starts a job that waits for kick-off from main
// + When job finishes, handoff result back to main via processing bool
void job(int32_t & shared) {
  std::unique_lock uniqueLock(mtx);
  cv.wait(uniqueLock, []()->bool {return processing;});
  std::cout << std::this_thread::get_id()
            << " thread_A: Initial value of shared = " << shared << std::endl;
  while (shared < INT32_MAX) {
    shared++;
  }
  // We're no longer processing data
  processing = false;
  std::cout << std::this_thread::get_id()
            << " thread_A: Done working." << std::endl;
  uniqueLock.unlock(); // Important! Unlock uniqueLock before we notify
  // Notify main that we've finished, so it can proceed
  cv.notify_one();
}

int main(const int argc, const char * argv[]) {
  std::cout << "main() thread id: " << std::this_thread::get_id() << std::endl;

  int32_t share = 0;
  std::thread thread_A(job, std::ref(share));

  mtx.lock();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  share = INT32_MAX / 2;
  processing = true;
  mtx.unlock();
  // Notify thread_A that its work can begin
  cv.notify_one();

  // Wait until thread_A finishes its work
  std::unique_lock uniqueLock(mtx);
  // Block execution until we are not processing
  cv.wait(uniqueLock, []()->bool { return !processing;});
  std::cout << std::this_thread::get_id() << " main(): final value of shared = "
            << share << std::endl;
  thread_A.join();

  return 0;
}
