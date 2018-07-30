# Nene Quest

## Overview
This is the implementation of 'Nene Quest' game which was appeared at the 'New Game!'.

## Build

### Prerequisites:
- Windows 10, Linux, or OSX (OS should be 64bit)
- Vcpkg
- CMake (>=3.8)
- *Visual Studio 2017 (on Windows)*

### Install libraries
Install 64bit static version of following libraries by using Vcpkg:
- OpenGL
- GLFW3
- GLEW
- GLM
- OpenAL-soft
- FreeType

For Windows,
```
> ./vcpkg install opengl:x64-windows-static
> ./vcpkg install glfw3:x64-windows-static
> ./vcpkg install glew:x64-windows-static
> ./vcpkg install glm:x64-windows-static
> ./vcpkg install openal-soft:x64-windows-static
> ./vcpkg install freetype:x64-windows-static
```

For Linux or OSX, change 'windows' to 'linux' or 'osx'.

If you want to use Visual Studio, then run the following to integrate the installed packages into the Visual Studio:
```
> ./vcpkg integrate install
```

### Build

For every OS,
```
> mkdir build
> cd build
> cmake .. -A x64 -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake --DVCPKG_TARGET_TRIPLET=x64-windows-static
```
${VCPKG_ROOT} is the path where the Vcpkg is installed.
For Linux or OSX, change 'windows' to 'linux' or 'osx'.

If you want to open cmake project using Visual Studio,
open 'CMakeSettings.json' and modify the path of cmakeCommandArgs-DCMAKE_TOOLCHAIN_FILE into ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
Next, open  the CMake project from the Visual Studio by opening 'CMakeLists.txt' file in the base directory.
