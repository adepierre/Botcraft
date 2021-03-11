![Linux](https://github.com/adepierre/Botcraft/workflows/Linux/badge.svg) ![Windows](https://github.com/adepierre/Botcraft/workflows/Windows/badge.svg)

# Botcraft

Botcraft is a cross-platform C++ library to connect and interact with Minecraft servers with (optional) integrated OpenGL renderer.

This was my first project using OpenGL, multi-threading, networking and "sort-of-complete cmake" so it's a "learn-by-doing" code and many things are probably (really) badly done or should be refactored. Do not hesitate to open an issue or to send a PR if you know how to improve some part of it!

## Features

- Connection to minecraft server (both offline mode and online connection with Mojang account)
- DNS name resolution with and without SRV record
- All official releases from 1.12.2 to 1.16.5 supported
- Compression
- Physics and collisions
- (Optional) Rendering of all the blocks (including entity-blocks like chests, banners...)
- Bot control with mouse and keyboard
- Path finding
- Block breaking
- Inventory managing
- Block placing
- Block interaction (button, lever etc...)

Example of pathfinding. Right of the screen is the integrated renderer
![](gifs/video.gif)

Example of block placing and inventory managing. Right of the screen is the integrated renderer
![](gifs/beacon.gif)

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

The code is cross-platform and is automatically built on both Windows with Visual 2019 and Linux at each push. It should also work on reasonably older versions of Visual Studio and macOS as well.

## Building and Installation

To build the library for the latest version of the game with both encryption and compression support and without OpenGL rendering:
```
git clone https://github.com/adepierre/Botcraft.git
cd Botcraft
mkdir build
cd build
cmake -DGAME_VERSION=latest -DBOTCRAFT_BUILD_EXAMPLES=ON -DBOTCRAFT_COMPRESSION=ON -DBOTCRAFT_ENCRYPTION=ON -DBOTCRAFT_USE_OPENGL_GUI=OFF ..
make all
make install
```

You don't have to clone the dependencies manually, cmake will clone the ones you need depending on your build configuration.

Don't forget to change the cmake install directory if you don't want the library to be installed in the default location.

On Windows with Visual, you can replace the last five steps by launching cmake-gui and then compiling the .sln from Visual.

There are several cmake options you can modify:
- GAME_VERSION [1.XX.X or latest]
- BOTCRAFT_BUILD_EXAMPLES [ON/OFF]
- BOTCRAFT_INSTALL_ASSETS [ON/OFF] Copy all the needed assets to the installation folder along with the library and executable
- BOTCRAFT_COMPRESSION [ON/OFF] Add compression ability, must be ON to connect to a server with compression enabled
- BOTCRAFT_ENCRYPTION [ON/OFF] Add encryption ability, must be ON to connect to a server in online mode
- BOTCRAFT_USE_OPENGL_GUI [ON/OFF] If ON, botcraft will be compiled with the OpenGL GUI enabled
- BOTCRAFT_USE_IMGUI [ON/OFF] If ON, additional information will be displayed on the GUI (need BOTCRAFT_USE_OPENGL_GUI to be ON)

## Examples

Examples can be found in the [Examples](Examples/) folder:
- [0_HelloWorld](Examples/0_HelloWorld): Connect to a server, sends Hello World! in the chat then disconnect
- [1_UserControlledExample](Examples/1_UserControlledExample): Best with GUI, mouse and keyboard controlled player. Can be used in a dummy world (without any server) to test things like physics or rendering
- [2_ChatCommandExample](Examples/2_ChatCommandExample): Simple bot that obey commands sent through vanilla chat. Known commands at this point:
  - pathfinding
  - disconnecting 
  - checking its sourroundings for spawnable blocks (useful if you want to check whether or not a perimeter is spawn proof)
  - placing a block
  - interacting with a block (lever, button ...)
- [3_SimpleAFKExample](Examples/3_SimpleAFKExample): Simple example to stay at the same position. Physics is not processed, chunks are not saved in memory to save RAM.

## Microsoft accounts system

It is too difficult to replicate Microsoft's Oauth algorithms properly so we introduced "helper" feature to make it work properly.
If you log in inside official launcher it will create launcher_accounts.json file in .minecraft directory, specify path to it (starts with '.' or '/') as a username (any password, will be ignored anyways) and Authentifier will grab credentials (uuid, nickname and token) from this file.
Example: `1_UserControlledExample_d 1 myserver.works /home/max/.minecraft/launcher_accounts.json 1`
The only downside is that it needs to be refreshed after a week or so, field accessTokenExpiresAt indicates that but I did not implemented a check so if you are getting 403 out of nowhere it might be it, to solve it just open up official launcher and it will renew it for you

## To-do list

It's only a free time project, but there are still a lot of things to do! Right now the only usecase is an AFK bot to activate a farm with almost 0% usage of CPU/GPU. The next step is to add some functionalities like entities handling/rendering, attacking, crafting... Everything needed to automate more tasks in survival vanilla Minecraft!

There are also some minor improvements to existing features that have to be done:
- Improve water/lava/ladder physics (the player can walk on fluids and can't climb the ladders)
- Improve pathfinding with real colliders (the pathfinding considers every solid block as box of size 1 but the collisions are computed with the real shapes which lead to bad situations, for example with fences)

## License

GPL v3
