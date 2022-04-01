/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a race condition problem and solution                 ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void problem() {
  std::vector<std::thread> threads;
  const uint8_t thread_count = 5;
  // With no mutex lock, the final value will vary in the range 1000000-5000000
  // + Threads will modify x simultaneously, so some iterations will be lost
  // + x will have same initial value entering this loop on different threads
  uint32_t x = 0;
  for (uint8_t i = 0; i < thread_count; i++) {
    threads.emplace_back([&x](){
      for (uint32_t i = 0; i < 1000000; i++) {
        x = x + 1;
      };
    });
  }
  // Ensure the function doesn't continue until all threads are finished
  // + There's no issue here, the issue is in how `x` is accessed above
  for (auto &thread : threads) thread.join();
  std::cout << x << std::endl;
}

// Create mutex lock to prevent threads from modifying same value simultaneously
static std::mutex mtx;
void solution() {
  std::vector<std::thread> threads;
  const uint8_t thread_count = 5;
  uint32_t x = 0;
  for (uint8_t i = 0; i < thread_count; i++) {
    threads.emplace_back([&x](){
      // The first thread that arrives here will 'lock' other threads from passing
      // + Once first thread finishes, the next thread will resume
      // + This process repeats until all threads finish
      std::lock_guard<std::mutex> lock(mtx);
      for (uint32_t i = 0; i < 1000000; i++) {
        x = x + 1;
      };
    });
  }
  // Ensure the function doesn't continue until all threads are finished
  for (auto &thread : threads) thread.join();
  std::cout << x << std::endl;
}

int main(const int argc, const char * argv[]) {
  // Result will vary from 1000000-5000000
  problem();

  // Result will always be 5000000
  solution();
  return 0;
}
