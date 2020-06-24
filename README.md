
# Botcraft

Botcraft is a cross-platform C++ library to connect and interact with Minecraft servers with (optional) integrated OpenGL renderer.

This was my first project using OpenGL, multi-threading, networking and "sort-of-complete cmake" so it's a "learn-by-doing" code and many things are probably (really) badly done or should be refactored. Do not hesitate to open an issue or to send a PR if you know how to improve some part of it!

## Features

- Connection to minecraft server (both offline mode and online connection with Mojang account)
- Versions 1.12.2, 1.13, 1.13.1, 1.13.2, 1.14, 1.14.1, 1.14.2, 1.14.3, 1.14.4, 1.15, 1.15.1 and 1.15.2 supported
- Compression
- Physics and collisions
- (Optional) Rendering of all the blocks (not entities)
- Bot control with mouse and keyboard
- Path finding
- Block breaking

Example of pathfinding. Right of the screen is the integrated renderer
![](video.gif)

## Dependencies

All the libraries are included either directly or as submodules and are built locally automatically (if not already found on your system) so you don't have to do anything.

- [asio](https://think-async.com/Asio/)
- [picoJson](https://github.com/kazuho/picojson)
- [zlib](https://github.com/madler/zlib) (optional, used only if compression is enabled on your server)
- [openssl](https://www.openssl.org/) (optional, used only if your server is in online mode)

Optional dependencies (needed only if you want to build the OpenGL renderer)
- [stb_image](https://github.com/nothings/stb)
- [glad](https://glad.dav1d.de/)
- [glfw](https://github.com/glfw/glfw)
- [glm](https://github.com/g-truc/glm)
- [imgui](https://github.com/ocornut/imgui)
- [rectpack2D](https://github.com/TeamHypersomnia/rectpack2D)

I only regularly test the code on Windows with Visual 2019 but it should also work with older versions (from 2013 to 2017). All the code is cross-platform so it should also work on Linux and macOS. I made some modifications to fix the errors, the code is currently compiling on a raspberry pi.

## Building and Installation

```
git clone https://github.com/adepierre/Botcraft.git
cd botcraft
mkdir build
cd build
cmake ..
make all
make install
```

You don't have to clone the dependencies manually, cmake will clone the ones you need depending on your build configuration.

Don't forget to change the cmake install directory if you don't want the library to be installed in the default location.

On Windows with Visual, you can replace the last five steps by launching cmake-gui and then compiling the .sln from Visual.

There are several cmake options you can modify:
- GAME_VERSION [1.12.2, 1.13, 1.13.1, 1.13.2, 1.14, 1.14.1, 1.14.2, 1.14.3, 1.14.4, 1.15, 1.15.1, 1.15.2]
- BOTCRAFT_BUILD_EXAMPLES [ON/OFF]
- BOTCRAFT_INSTALL_ASSETS [ON/OFF] Copy all the needed assets to the installation folder along with the library and executable
- BOTCRAFT_COMPRESSION [ON/OFF] Add compression ability, must be ON to connect to a server with compression enabled
- BOTCRAFT_ENCRYPTION [ON/OFF] Add encryption ability, must be ON to connect to a server in online mode
- BOTCRAFT_USE_OPENGL_GUI [ON/OFF] If ON, botcraft will be compiled with the OpenGL GUI enabled
- BOTCRAFT_USE_IMGUI [ON/OFF] If ON, additional information will be displayed on the GUI (need BOTCRAFT_USE_OPENGL_GUI to be ON)

## Examples

Three examples can be found in the [Examples](Examples/) folder:
- [0_HelloWorld](Examples/0_HelloWorld): Connect to a server, send Hello World! in the chat then disconnect
- [1_UserControlledExample](Examples/1_UserControlledExample): Best with GUI, mouse and keyboard controlled player. Can be used in a dummy world (without any server) to test things like physics or rendering
- [2_ChatCommandExample](Examples/2_ChatCommandExample): Simple bot that obey commands sent through vanilla chat. Knows three commands at this point, pathfinding, disconnecting and checking its sourroundings for spawnable blocks (useful if you want to check whether or not a perimeter is spawn proof).
- [3_SimpleAFKExample](Examples/3_SimpleAFKExample): Simple example to stay at the same position. Physics is not processed, chunks are not saved in memory to save RAM.

## To-do list

It's only a free time project, but there are still a lot of things to do! Right now the only usecase is an AFK bot to activate a farm with almost 0% usage of CPU/GPU. The next step is to add some functionalities like block breaking with a tool and block placing, inventory managing, entities handling/rendering, attacking, crafting... Everything needed to automate more tasks in survival vanilla Minecraft!

There are also some minor improvements to existing features that have to be done:
- Improve water/lava/ladder physics (the player can walk on fluids and can't climb the ladders)
- Improve pathfinding with real colliders (the pathfinding considers every solid block as box of size 1 but the collisions are computed with the real shapes which lead to bad situations, for example with fences)

## License

GPL v3
