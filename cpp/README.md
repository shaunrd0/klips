# cpp

```bash
shaunrd0/klips/cpp/
├── algorithms     # Examples of various algorithms written in C++
├── cmake          # Example of using cmake to build and organize larger projects
├── cryptography   # Examples of encrypting / decrypting using ciphers in C++
├── datastructs    # Collection of useful datastructures written in C++
├── graphics       # Examples of graphics projects written in C++
├── multithreading # Basic multithreading examples in C++
├── patterns       # Examples of various design patterns written in C++
├── qt             # Qt project examples using C++
└── README.md
```

This directory contains a `CMakeLists.txt`, which can be selected to open as a
project within your preferred IDE. From there, all nested examples can be built,
debugged, and ran.

Some of the more recent projects in this repository requires the latest CMake LTS.
To install `cmake` LTS with `apt` we can follow [official instructions from kitware](https://apt.kitware.com/)
Alternatively, we can install the LTS with python's `pip`.
```bash
sudo apt install python3.9 python3-pip
sudo apt purge cmake
python3.9 -m pip install -U pip
python3.9 -m pip install --upgrade cmake
# The command below is optional if you have added the python binary path to your PATH environment variable
sudo ln -s /usr/local/lib/python3.9/dist-packages/cmake/data/bin/cmake /usr/bin/
cmake --version

cmake version 3.22.1
```

Once cmake is installed, dependencies for all examples can be installed with the command below.
```bash
sudo apt install libsdl2-dev freeglut3-dev
```

If we build from this directory, we build all C++ projects and examples
```bash
cd /path/to/klips/cpp/
mkdir build && cd build
cmake .. && cmake --build .
```

We can see the binaries output in the `build/bin/` folder
```bash
~/Code/klips/cpp/build$ ls bin/
abstract-factory-test        graph-test-templated  SingleListDriver
adapter-test                 graph-test-weighted   singleton-test
bridge-test                  HeapDriver            StackDriver
bubble-sort                  heap-sort             state-test
bucket-sort                  insertion-sort        TemplatedDoubleListDriver
CircleDoubleDriver           merge-sort            TemplatedQueueDriver
CircleSingleDriver           observer-test         TemplatedStackDriver
columnar-transposition-test  opengl-test           TemplatedVectorDriver
counting-sort                prototype-test        test-bst
DoubleListDriver             QueueDriver           test-bst-algo
execute-hello                quick-sort            test-redblack
factory-test                 radix-sort            VectorDriver
graph-test-object            sdl-test              visitor-test
graph-test-simple            select-sort
```

We can also build from subdirectories.
To only build projects related to design patterns we build from the `patterns/` subdirectory, for example
```bash
cd /path/to/klips/cpp/patterns
mkdir build && cd build
cmake .. && cmake --build .
```

And we can again see the binaries output in the `build/bin/` folder
```bash
~/Code/klips/cpp/patterns/build$ ls bin/
abstract-factory-test  bridge-test   observer-test   singleton-test  visitor-test
adapter-test           factory-test  prototype-test  state-test
```

If cmake is not being used in a project, it can be built with `g++` manually using
the commands outlined in `*/.vscode/tasks.json`, or by using VSCode to open the example
and running the build task.
Check the header comments in the main source file for the example for instructions.
