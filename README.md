# COSC345

[![CMake](https://github.com/wpframe/cosc345/actions/workflows/cmake.yml/badge.svg)](https://github.com/wpframe/cosc345/actions/workflows/cmake.yml)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/7c00e5e5cadf446ba718ddb5ac70192f)](https://app.codacy.com/gh/wpframe/cosc345/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![Documentation](https://codedocs.xyz/wpframe/cosc345.svg)](https://codedocs.xyz/wpframe/cosc345/)


Team members:
  - Ben Knox
  - Shamen Kumar
  - Vincent Lee
  - Will Frame

[Our report](docs/assignment1.md)

To build, simply run [build.sh](build.sh) with ``./build.sh`` with CMake installed.

If you run into issues with that, here is a breakdown:

 1. Install [CMake](https://cmake.org/install/)
 2. Make a /build/ directory in terminal (``mkdir build``)
 3. Open the build directory (``cd build``)
 4. Run ``cmake ..``
 5. Run ``cmake --build . --config Release``

To open the application, run [build/MyApp](build/MyApp) with ``./MyApp``
