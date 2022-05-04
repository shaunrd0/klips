# Multithreading

A few basic multithreading programs written in C++ while learning about 
the [concurrency support library](https://en.cppreference.com/w/cpp/thread)

```
klips/cpp/multithreading
.
├── conditions     # Using condition_variable to control job execution flow
├── deadlock       # Example of problem and solution for deadlocks
├── livelock       # Example of problem and solution for livelocks
├── race-condition # Example of problem and solution for race conditions
└── README.md
```

We can build the examples with the following commands.

```bash
cd /path/to/klips/cpp/multithreading/
mkdir build && cd build
cmake .. && cmake --build .
ls bin/

multithread-conditions  multithread-deadlock  multithread-livelock  multithread-race-condition
```
