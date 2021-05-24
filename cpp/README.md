# Cpp

```
shaunrd0/klips/cpp/
├── algorithms  # Examples of various algorithms written in C++
├── cmake       # Example of using cmake to build and organize larger projects
├── datastructs # Collection of useful datastructures written in C++
├── opengl      # Barebones opengl application written in C++ built with gcc
├── patterns    # Examples of various design patterns written in C++
├── README.md
├── sdl-cmake   # Barebones sdl application written in C++ built with cmake
└── sdl         # Barebones sdl application written in C++ built with gcc
```

This directory contains a `CMakeLists.txt`, which can be selected to open as a 
project within your preferred IDE. From there, all nested examples can be built,
debugged, and ran.

In general, if a `CMakeLists.txt` is included in the project's root directory, 
we can build the example with the following commands

```
mkdir build && cd build
cmake .. && cmake --build .
```

If cmake is not being used in a project, it can be built with `g++` manually using
the commands outlined in `*/.vscode/tasks.json`, or by using VSCode to open the example
and running the build task.

