<p align="center">
    <img src="logo.png" alt="IME Logo">
</p>

# IME — Infinite Motion Engine

IME is a state-based 2D game engine. It is built on top of [SFML](https://www.sfml-dev.org/index.php)
using C++17

## Overview

This game engine is not the next big thing. I developed it to improve my
Object Oriented Programming (OOP) skills. Any constructive feedback is
welcome. You can post feedback or ask me questions [here](https://github.com/KwenaMashamaite/IME/discussions/)

## Features

* **Graphics** - Tilemap, Animatable Sprites, 2D camera, Spritesheet
* **GUI** - Label, Button, Checkbox, MenuBar, and much more thanks to a seamless [TGUI](https://tgui.eu/) integration
* **Animations** - 2D animations which support both spritesheet and texture atlas
* **Physics** - Path finding, grid based movement, grid cell based collisions, [Rigid body dynamics](https://www.toptal.com/game/video-game-physics-part-i-an-introduction-to-rigid-body-dynamics) 
  thanks to a seamless [Box2d](https://box2d.org/) integration, collision detection using contact callbacks: onBegin, onEnd and onStay
* **Input** - Keyboard and Mouse support
* **Sound** - Music and Sound effects
* **Event system** - Javascript inspired event system
* **Asset management** - Automated asset management system
* **Time** - Execute one time, repeating or infinite time-based callbacks

## Demos

Here is a list of games developed with IME:

1. [Namco's 1982 Super Pac-Man clone](https://github.com/KwenaMashamaite/SuperPacMan)

## Downloads

The latest official precompiled IME binaries can be downloaded [here](https://github.com/KwenaMashamaite/IME/releases/tag/v2.0.0).
To use the library you must have a C++17 compliant compiler. Available binaries are compiled 
with `GCC 10.2.0 MinGW` and `Microsoft Visual C++ 2019` compilers. This means that in order to use them, 
you must have the exact compiler on your system. If you want to use different versions of the above compilers
or a different compiler, then you have to build the library yourself. I have not tested different versions of GCC and 
VC++ but as long as they support C++17, they should work just fine.

## Installation

1. Using CMake

If you install IME in a known location `C:\Program Files (x86)`, you don't have to set `IME_DIR`,
CMake will automatically find the IME library

```cmake
# Find IME
set(IME_DIR "your_path_to_IME_directory_here/lib/cmake/IME") # Skip if installed in known location
find_package(IME 2.0.0 REQUIRED)

# Link IME
target_link_libraries (myGame PRIVATE ime)
```

Before running your game, copy the contents of `IME/bin` directory to the directory
in which your executable resides. If your current build type is **Debug**, then copy the
contents of `IME/bin/Debug` and if your build type is **Release** then copy the contents of 
`IME/bin/Release`. For `GCC 10.2.0 MinGW` compiler, you must also copy the contents of 
`IME/bin/Runtime` to your executables directory. 

##  Build

If you want to use IME with a different compiler, or you want to experiment with
it and figure out how it works then you must build it yourself:

1. Clone the repository
2. Download and Install [CMake 3.17+](https://cmake.org/)
3. Download and install IME's dependencies: [SFML 2.5.1](https://www.sfml-dev.org/index.php), [TGUI 0.9.1](https://tgui.eu/), and [Box2d 2.4.1](https://box2d.org/) <br>
   The dependencies must have a matching compiler and architecture (e.g, If you intend to build the library with <br>
   `Visual C++ 2017 (32-bit)`, then SFML, TGUI and Box2d binaries must all be compiled with `Visual C++ 2017 (32-bit)`
   <br>
   
4. Run the following commands from the project root directory:

```shell
mkdir build
cd build
cmake ..
cmake --build .
cmake --install . --prefix "directory_where_you_want_the_library_to_be_installed_after_build"
```

You can leave out `--prefix "installation_directory"` and CMake will install the library to 
`C:\Program Files (x86)\IME`. However, this may require the terminal to be run with admin privileges

## Learn

* [Tutorials](#Build) (Coming soon)
* [API Documentation](https://kwenamashamaite.github.io/IME/docs/v2.0.0/html/index.html)

## Platform

Currently, IME only supports Windows OS

## Developers

Name:  Kwena Mashamaite (Author)

Email: kwena.mashamaite1@gmail.com
 
## License

IME is released under the [MIT](https://opensource.org/licenses/MIT) license. See [LICENSE](LICENSE) file.
