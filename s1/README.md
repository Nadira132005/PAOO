# C++ static library and application

Requires CMake 3.16 or newer and a C++17 compiler.

This repository has a static library in `lib/` and an application in `app/`.
The library provides `aduna` and `inmulteste` in the C++ namespace
`calculator`, declared in `lib/include/calculator/Calculator.h`. The app links
to the library through the CMake target `Calculator::calculator`.

## Build both together

Run these commands from this directory:

```sh
cmake -S . -B build
cmake --build build
```

The build directory contains generated CMake files and compiled outputs. Run
the app with:

```sh
./build/app/app
```

The expected output is:

```text
6 + 3 = 9
6 * 3 = 18
```

With a multi-configuration generator, the executable may instead be under
`build/app/Debug/` or `build/app/Release/`.

## Install the library for other projects

The library also has install and package-export rules. To install it under the
repository's `install/` directory:

```sh
cmake -S lib -B build/lib -DCMAKE_INSTALL_PREFIX="$PWD/install"
cmake --build build/lib
cmake --install build/lib
```

Another CMake project can then locate it by setting
`CMAKE_PREFIX_PATH` to that install prefix and calling
`find_package(Calculator 1 CONFIG REQUIRED)`. The exported target is
`Lib::calculator`.
