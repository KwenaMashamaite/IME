<p align="center">
    <img src="logo.png" alt="IME Logo">
</p>

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

# IME — Infinite Motion Engine

IME is an open source state-based 2D game engine. It is written in C++17 and 
makes use of [SFML](https://github.com/SFML/SFML) and [TGUI](https://github.com/texus/TGUI).

## Overview

This game engine is not the next Unity or Godot. I developed it to improve my
Object Oriented Programming (OOP) skills and my knowledge of shared libraries
and build tools in C++. I would appreciate any constructive feedback.

## Features
 
* **Graphics** - Static tilemap, Sprites, GUI components (Label, Button, Checkbox, Input filed and much more)
* **Animations** - 2D animations which support both spritesheet and texture atlas
* **Physics** - Path finding, grid based movement, collision detection using callbacks
* **Input** - Mouse and Keyboard
* **Sound** - Music and Sound effects
* **Event system** - Javascript inspired event emitter
* **Asset management** - Just provide the filename and path to the asset and the engine will handle the rest
* **Time** - Execute functions after delays and intervals using callback system

## Demos

Here is a list of games developed with IME:

1. [Namco's 1982 Super Pac-Man clone](https://github.com/KwenaMashamaite/SuperPacMan)

## Downloads

The latest official IME binaries can be downloaded [here](https://github.com/KwenaMashamaite/IME/releases/latest/download/IME-1.0.0.zip). 
In addition, IME has dependencies on other libraries that must be downloaded.

- Download [SFML 2.5.1](https://github.com/KwenaMashamaite/IME/releases/latest/download/SFML-2.5.1.zip)
- Download [TGUI 0.9.0](https://github.com/KwenaMashamaite/IME/releases/latest/download/TGUI-0.9.0.zip)

##  Build

1. Clone the repository
2. Download [GCC 7.3.0 MinGW (32-bit)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download) compiler and [CMake 3.17+](https://cmake.org/download/)
3. Add the MinGW\bin directory to the PATH environment variable </br>
   _You can do it using **Windows PowerShell** with the following command:_
```shell
$Env:Path += ";your_mingw_folder\bin"
```
For example, adding **_C:\mingw64\bin_** to the value of the Path environment variable:

```shell
$Env:Path += ";C:\mingw64\bin"
```
3. Run the following commands from the project root directory:

```shell
mkdir build
cd build
cmake -G"MinGW Makefiles" ..
cmake --build .
cmake --install . --prefix "your_install_directory"
```

## Installation

1. Using CMake 
   
```cmake
# Find SFML
set(SFML_DIR "your_path_to_SFML_directory/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS REQUIRED system window graphics audio)

# Find TGUI
set(TGUI_DIR "your_path_to_TGUI_directory/lib/cmake/TGUI")
find_package(TGUI 0.9.0 REQUIRED)

# Find IME
set(IME_DIR "your_path_to_IME_directory/lib/cmake/IME")
find_package(IME 2.0.0 REQUIRED)

# Link TGUI, SFML and IME
target_link_libraries (myGame PRIVATE tgui sfml-graphics sfml-window sfml-system sfml-audio ime)
```

## Learn

* [Documentation](https://kwenamashamaite.github.io/IME/docs/v1.0.0/index.html)

## Platform

Currently, IME only supports Windows OS

## Contact

Name: Kwena Mashamaite (Author)

Email: kmash.ime@gmail.com
 
## License

IME is released under the [MIT](https://opensource.org/licenses/MIT) license. See [LICENSE](LICENSE) file.
