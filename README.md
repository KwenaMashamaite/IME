<p align="center">
    <img src="logo.png" alt="IME Logo">
</p>

# IME — Infinite Motion Engine

IME is a state-based game engine for developing 2D games on the Windows platform. It is written in C++17.

_**Note** - This project has been retired (life cycle: 23 January 2020 - 24 April 2022). This means that IME will no longer receive new
features and bug fixes. The last stable IME version is `v3.2.0`_

## Features

* **Graphics** - Render Window, 2D grid, Animatable Sprites, 2D camera, Spritesheet, etc...
* **GUI** - Label, Button, Checkbox, MenuBar, and much more
* **Animations** - 2D animations which support both spritesheet and texture atlas
* **Physics** - Path finding, Grid based movement, Grid cell based collisions, Rigid body physics engine,
  Collision detection using contact callbacks
* **Input** - Keyboard, Mouse and Joystick support
* **Sound** - Music and Sound effects support
* **Event system** - Thread safe event system
* **Asset management** - Automated resource management system
* **Scene management** - Last In First Out (LIFO) scene management
* **Time** - Schedule one time, repeating or indefinite callbacks

*IME does not support an Editor*

## Demos

Here is a list of games developed with IME:

1. [Pac-Man arcade game clone](https://github.com/KwenaMashamaite/PacMan)
2. [Super Pac-Man arcade game clone](https://github.com/KwenaMashamaite/SuperPacMan)
2. [Galaxian arcade game clone](https://github.com/KwenaMashamaite/Galaxian)

## Downloads

The latest official precompiled IME binaries can be downloaded [here](https://github.com/KwenaMashamaite/IME/releases/tag/v3.2.0).
To use the library you must have a supported (GCC or VC++) C++17 compliant compiler.
Available binaries are compiled with `GCC MinGW 11.2.0` and `Microsoft Visual C++ 16/17`
compilers. This means that in order to use them, you must have the exact compiler on your system.
If you want to use different versions of the above compilers, then you'll have to [build](#Build) the
library yourself.

## Installation

1. Using CMake

If you extracted IME to a location known to *CMAKE*, you don't have to
set `IME_DIR`, *CMake* will automatically find the library

```cmake
# Find IME
set(IME_DIR "your_path_to_IME_directory_here/lib/cmake/IME") # Skip if IME installed in known location
find_package(ime 3.2.0 REQUIRED)

# Link IME
target_link_libraries(myGame PRIVATE ime)
```
<br>

<em>Note:</em>

After successfully building your game executable, copy the contents of `IME/bin` folder to the
folder in which your game executable resides. If your current `BUILD_TYPE` is **Debug**, then copy
the contents of `IME/bin/Debug` and if it is **Release**, then copy the contents of `IME/bin/Release`.
You must also copy the contents of `IME/bin/Runtime` regardless of the current build type.

##  Build

If you want to use *IME* with a different compiler, then you must build it yourself:

1. Clone the repository
2. Download and Install [CMake 3.17+](https://cmake.org/)
3. Download and install *IME*'s dependencies: [SFML 2.5.1](https://www.sfml-dev.org/index.php), [TGUI 0.9.3](https://tgui.eu/), and [Box2d 2.4.1](https://box2d.org/) <br>
   The dependencies must have a matching compiler and architecture (e.g, If you intend to build *IME* with <br>
   `GCC MinGW 11.2.0 (32-bit)`, then *SFML*, *TGUI* and *Box2d* binaries must all be compiled with `GCC MinGW 11.2.0 (32-bit)`
   <br>

4. Run the following commands from the project root directory:

```shell
mkdir build
cd build
cmake ..
cmake --build .
cmake --install . --prefix "directory_where_you_want_the_library_to_be_installed_after_build"
```

You can leave out `--prefix "installation_directory"` and *CMake* will install the library to a known
location, usually `Program Files`. However, this may require admin privileges

## Learn

* [Tutorials](#Learn) (Coming soon)
* [API Documentation](https://kwenamashamaite.github.io/IME/docs/v3.2.0/html/index.html)

## Platform

Currently, IME only supports Windows OS

## Developers

Name:  Kwena Mashamaite (Author)

Email: kwena.mashamaite1@gmail.com

For any feature suggestions, feedback or questions, you can get in touch with me [here](https://github.com/KwenaMashamaite/IME/discussions/).

## License

IME is released under the [MIT](https://opensource.org/licenses/MIT) license. See [LICENSE](LICENSE) file.
