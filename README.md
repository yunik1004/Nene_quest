# Nene Quest

## Overview
This is the implementation of 'Nene Quest' game which was appeared at the 'New Game'.

## Build

### Prerequisites:
- Windows 10, Linux, or OSX (OS should be 64bit)
- Vcpkg
- CMake (>=3.8)
- *Visual Studio 2017 (on Windows)*

### Install libraries
Install 64bit version of OpenGL, GLFW3, GLEW, GLM by using Vcpkg

For Windows,
```
> ./vcpkg install opengl:x64-windows
> ./vcpkg install glfw3:x64-windows
> ./vcpkg install glew:x64-windows
> ./vcpkg install glm:x64-windows
```

For Linux or OSX, change 'windows' to 'linux' or 'osx'.

### Build

For every OS,
```
> mkdir build
> cd build
> cmake .. -A x64 -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
```
${VCPKG_ROOT} is the path where the Vcpkg is installed.

If you want to open cmake project using visual studio,
open 'CMakeSettings.json' and modify the path of cmakeCommandArgs-DCMAKE_TOOLCHAIN_FILE into ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake