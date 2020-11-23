# Cpp

```
shaunrd0/klips/cpp/
├── cmake       # Example of using cmake to build and organize larger projects
├── datastructs # Collection of useful datastructures written in C++
├── opengl      # Barebones opengl application written in C++ built with make
├── README.md
├── sdl         # Barebones sdl application written in C++ built with make
└── sdl-cmake   # Barebones sdl application written in C++ built with cmake
```


In general, if a `CMakeLists.txt` is included in the project's root directory, 
we can build the example with the following commands

```
mkdir build && cd build
cmake .. && cmake --build .
```


If cmake is not being used in a project, it can be built with `g++` manually using
the commands outlined in `*/.vscode/tasts.json`, or by using VSCode to open the example
and running the build task.
