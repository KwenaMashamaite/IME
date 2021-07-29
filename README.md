<p align="center">
    <img src="logo.png" alt="IME Logo">
</p>

# IME — Infinite Motion Engine

IME is a framework for developing 2D games. It is built on top of [SFML](https://www.sfml-dev.org/index.php)
using C++17. IME is state-based, this means that your game is treated as a collection of
distinct game states that are active one at a time. For states that need to share information
with each other, IME provides an engine level caching system which can store data of any kind
that can be accessed by any state at any given time.

For any feature suggestions, feedback or questions, please do that [here](https://github.com/KwenaMashamaite/IME/discussions/)

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

The latest official precompiled IME binaries can be downloaded [here](https://github.com/KwenaMashamaite/IME/releases/tag/v2.2-beta).
To use the library you must have a supported (GCC or VC++) C++17 compliant compiler. 
Available binaries are compiled with `GCC MinGW: 7.3.0, 10.2.0` and `Microsoft Visual C++ 16 2019` 
compilers. This means that in order to use them, you must have the exact compiler on your system. 
If you want to use different versions of the above compilers, then you have to [build](#Build) the 
library yourself.

## Installation

1. Using CMake

If you install IME in a known location, usually `Program Files (x86)`, you don't have to 
set `IME_DIR`, *CMake* will automatically find the library

```cmake
# Find IME
set(IME_DIR "your_path_to_IME_directory_here/lib/cmake/IME") # Skip if IME installed in known location
find_package(IME 2.2.0 REQUIRED)

# Link IME
target_link_libraries (myGame PRIVATE ime)
```
<br>

After successfully building your game executable, copy the contents of `IME/bin` folder to the
folder in which your game executable resides. If your current `BUILD_TYPE` is **Debug**, then copy 
the contents of `IME/bin/Debug` and if it is **Release**, then copy the contents of `IME/bin/Release`. 
For `GCC MinGW` compilers, you must also copy the contents of `IME/bin/Runtime` to your game executables 
folder. For `VC++` compilers, you should only copy the contents of `IME/bin/Runtime` if you don't have 
[Visual C++ Redistributable Runtimes](https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0) 
installed on your system. Note that copying the contents of `IME/bin/BUILD_TYPE` applies to both `dynamic` 
and `static` linking to *IME*. However, for `static` linking, you only need to copy 
`IME/bin/Debug/openal32.dll` or `IME/bin/Release/openal32.dll` to your game directory.

##  Build

If you want to use *IME* with a different compiler, then you must build it yourself:

1. Clone the repository
```git
$ git clone https://github.com/KwenaMashamaite/IME
```

2. Download and Install [CMake 3.17+](https://cmake.org/)
3. Download and install *IME*'s dependencies: [SFML 2.5.1](https://www.sfml-dev.org/index.php), [TGUI 0.9.1](https://tgui.eu/), and [Box2d 2.4.1](https://box2d.org/) <br>
   The dependencies must have a matching compiler and architecture (e.g, If you intend to build *IME* with <br>
   `Visual C++ 15 2017 (32-bit)`, then *SFML*, *TGUI* and *Box2d* binaries must all be compiled with `Visual C++ 15 2017 (32-bit)`
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
location, usually `Program Files (x86)\IME`. However, this may require admin privileges

## Learn

* [Tutorials](#Learn) (Coming soon)
* [API Documentation](https://kwenamashamaite.github.io/IME/docs/v2.2-beta/html/index.html)

## Platform

Currently, IME only supports Windows OS

## Developers

Name:  Kwena Mashamaite (Author)

Email: kwena.mashamaite1@gmail.com
 
## License

IME is released under the [MIT](https://opensource.org/licenses/MIT) license. See [LICENSE](LICENSE) file.
