/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example and solution for livelocks in C++                        ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

static std::mutex mtx_A, mtx_B, output;

// Helper function to output thread ID and string associated with mutex name
// + This must also be thread-safe, since we want threads to produce output
// + There is no bug or issue here; This is just in support of example output
void print_safe(const std::string & s) {
  std::scoped_lock<std::mutex> scopedLock(output);
  std::cout << s << std::endl;
}

void problem() {
  // Construct a vector with 5 agreed-upon times to synchronize loops in threads
  typedef std::chrono::time_point<std::chrono::steady_clock,
      std::chrono::steady_clock::duration> time_point;
  std::vector<time_point> waitTime(6);
  for (uint8_t i = 0; i < 6; i++) {
    waitTime[i] = std::chrono::steady_clock::now()+std::chrono::seconds(1+i);
  }

  std::thread thread_A([waitTime]()->void {
    uint8_t count = 0; // Used to select time slot from waitTime vector
    bool done = false;
    while (!done) {
      count++;
      std::lock_guard l(mtx_A);
      std::cout << std::this_thread::get_id() << " thread_A: Lock A\n";
      // Wait until the next time slot to continue
      // + Helps to show example of livelock by ensuring B is not available
      std::this_thread::sleep_until(waitTime[count]);
      std::cout << std::this_thread::get_id() << " thread_A: Requesting B\n";
      if (mtx_B.try_lock()) {
        done = true;
        std::cout << std::this_thread::get_id()
                  << " thread_A: Acquired locks for A, B! Done.\n";
      }
      else {
        std::cout << std::this_thread::get_id()
                  << " thread_A: Can't lock B, unlocking A\n";
      }
    }
    mtx_B.unlock();
  });

  std::thread thread_B([waitTime]()->void {
    // As an example, enter livelock for only 5 iterations
    // + Also used to select time slot from waitTime vector
    uint8_t count = 0;
    bool done = false;
    while (!done && count < 5) {
      count++;
      std::lock_guard l(mtx_B);
      // Wait until the next time slot to continue
      // + Helps to show example of livelock by ensuring A is not available
      std::this_thread::sleep_until(waitTime[count]);
      if (mtx_A.try_lock()) {
        // The program will never reach this point in the code
        // + The only reason livelock ends is because count > 5
        done = true;
      }
    }
  });

  thread_A.join();
  thread_B.join();
}

// The solution below uses std::scoped_lock to avoid the livelock problem
void solution() {
  std::thread thread_A([]()->void {
    for (int i = 0; i < 5; i++) {
      // Increase wait time with i
      // + To encourage alternating lock ownership between threads
      std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
      std::scoped_lock l(mtx_A, mtx_B);
      std::cout << std::this_thread::get_id()
                << " thread_A: Acquired locks for A, B!" << std::endl;
    }
  });

  std::thread thread_B([]()->void {
    for (int i = 0; i < 5; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
      std::scoped_lock l(mtx_B, mtx_A);
      std::cout << std::this_thread::get_id()
                << " thread_B: Acquired locks for B, A!" << std::endl;
    }
  });

  thread_A.join();
  thread_B.join();
}

int main(const int argc, const char * argv[]) {
  std::cout << "main() thread id: " << std::this_thread::get_id() << std::endl;

  problem();

  std::cout << "\nSolution:\n\n";
  solution();

  return 0;
}
