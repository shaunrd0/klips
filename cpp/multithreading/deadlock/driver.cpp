/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example and solution for deadlocks in C++                        ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

static std::mutex mtx_A, mtx_B, output;

// Helper function to output thread ID and string associated with mutex name
// + This must also be thread-safe, since we want threads to produce output
// + There is no bug or issue here; This is just in support of example output
void print_safe(const std::string & s) {
  std::scoped_lock<std::mutex> scopedLock(output);
  std::cout << s << std::endl;
}

// Helper function to convert std::thread::id to string
std::string id_string(const std::thread::id & id) {
  std::stringstream stream;
  stream << id;
  return stream.str();
}

// In the two threads within this function, we have a problem
// + The mutex locks are acquired in reverse order, so they collide
// + This is called a deadlock; The program will *never* finish
void problem() {
  std::thread thread_A([]()->void {
    mtx_A.lock();
    print_safe(id_string(std::this_thread::get_id()) + " thread_A: Locked A");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx_B.lock(); // We can't lock B! thread_B is using it
    // The program will never reach this point in execution; We are in deadlock
    print_safe(id_string(std::this_thread::get_id())
               + " thread_A: B has been unlocked, we can proceed!\n  Locked B"
    );
    std::this_thread::sleep_for(std::chrono::seconds(1));

    print_safe(id_string(std::this_thread::get_id())
               + " thread_A: Unlocking A, B..."
    );
    mtx_A.unlock();
    mtx_B.unlock();
  });

  std::thread thread_B([]()->void {
    mtx_B.lock();
    print_safe(id_string(std::this_thread::get_id()) + " thread_B: Locked B");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx_A.lock(); // We can't lock A! thread_A is using it
    // The program will never reach this point in execution; We are in deadlock
    print_safe(id_string(std::this_thread::get_id())
               + " thread_B: A has been unlocked, we can proceed!\n  Locked A"
    );
    std::this_thread::sleep_for(std::chrono::seconds(1));

    print_safe(id_string(std::this_thread::get_id())
               + " thread_B: Unlocking B, A..."
    );
    mtx_B.unlock();
    mtx_A.unlock();
  });

  // This offers a way out of the deadlock, so we can proceed to the solution
  std::this_thread::sleep_for(std::chrono::seconds(2));
  char input;
  print_safe("\n"
             + id_string(std::this_thread::get_id())
             + " problem(): We are in a deadlock. \n"
             + "    Enter y/Y to continue to the solution...\n"
  );
  while (std::cin >> input) {
    if (input != 'Y' && input != 'y') continue;
    else break;
  }
  print_safe(id_string(std::this_thread::get_id())
             + " problem(): Unlocking A, B..."
  );
  mtx_A.unlock();
  mtx_B.unlock();

  thread_A.join();
  thread_B.join();
}

// std::lock will lock N mutex locks
// + If either is in use, execution will block until both are available to lock
void solution_A() {
  std::thread thread_A([]()->void {
    std::lock(mtx_A, mtx_B);
    print_safe(id_string(std::this_thread::get_id()) + ": Locked A, B");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    print_safe(id_string(std::this_thread::get_id()) + ": Unlocking A, B...");
    mtx_A.unlock();
    mtx_B.unlock();
  });

  std::thread thread_B([]()->void {
    std::lock(mtx_B, mtx_A);
    print_safe(id_string(std::this_thread::get_id()) + ": Locked B, A");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    print_safe(id_string(std::this_thread::get_id()) + ": Unlocking B, A...");
    mtx_B.unlock();
    mtx_A.unlock();
  });

  thread_A.join();
  thread_B.join();
}

// std::lock_guard is a C++11 object which can be constructed with 1 mutex
// + When the program leaves the scope of the guard, the mutex is unlocked
void solution_B() {
  std::thread thread_A([]()->void {
    // lock_guard will handle unlocking when program leaves this scope
    std::lock_guard<std::mutex> guard_A(mtx_A), guard_B(mtx_B);
    print_safe(id_string(std::this_thread::get_id()) + ": Locked A, B");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    print_safe(id_string(std::this_thread::get_id()) + ": Unlocking A, B...");
    // We don't need to explicitly unlock either mutex
  });

  std::thread thread_B([]()->void {
    std::lock_guard<std::mutex> guard_B(mtx_B), guard_A(mtx_A);
    print_safe(id_string(std::this_thread::get_id()) + ": Locked B, A");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    print_safe(id_string(std::this_thread::get_id()) + ": Unlocking B, A...");
    // We don't need to explicitly unlock either mutex
  });

  thread_A.join();
  thread_B.join();
}

// std::scoped_lock is a C++17 object that can be constructed with N mutex
// + When the program leaves this scope, all N mutex will be unlocked
void solution_C() {
  std::thread thread_A([]()->void {
    // scoped_lock will handle unlocking when program leaves this scope
    std::scoped_lock scopedLock(mtx_A, mtx_B);
    print_safe(id_string(std::this_thread::get_id()) + ": Locked A, B");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    print_safe(id_string(std::this_thread::get_id()) + ": Unlocking A, B...");
    // We don't need to explicitly unlock either mutex
  });

  std::thread thread_B([]()->void {
    std::scoped_lock scopedLock(mtx_B, mtx_A);
    print_safe(id_string(std::this_thread::get_id()) + ": Locked B, A");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    print_safe(id_string(std::this_thread::get_id()) + ": Unlocking B, A...");
    // We don't need to explicitly unlock either mutex
  });

  thread_A.join();
  thread_B.join();
}

int main(const int argc, const char * argv[]) {
  std::cout << "main() thread id: " << std::this_thread::get_id() << std::endl;

  problem();

  print_safe("\nsolution_A, using std::lock\n");
  solution_A();

  print_safe("\nsolution_B, using std::lock_guard\n");
  solution_B();

  print_safe("\nsolution_C, using std::scoped_lock\n");
  solution_C();

  return 0;
}
