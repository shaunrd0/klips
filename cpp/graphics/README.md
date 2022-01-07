# Graphics

Example graphics programming projects written in C++. 
For a more complete example of a graphics application, see [shaunrd0/qtk](https://gitlab.com/shaunrd0/qtk)

```
klips/cpp/graphics
.
├── opengl      # Barebones opengl application written in C++ built with gcc
├── opengl-cmake# Barebones opengl application written in C++ built with cmake
├── sdl-cmake   # Barebones sdl application written in C++ built with cmake
└── sdl         # Barebones sdl application written in C++ built with gcc
```

Install dependencies for these examples with the following command

```bash
sudo apt install libsdl2-dev freeglut3-dev 
```

Then we can build the examples that have `CMakeLists.txt` configured.
If the example does not use CMake, the commands to build and run are found within the header comments of the main source file.

```bash
cd /path/to/klips/cpp/graphics/
mkdir build && cd build
cmake .. && cmake --build .
ls bin/

opengl-test  sdl-test
```
