cmake_minimum_required(VERSION 3.12)

project(Botcraft)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
cmake_policy(SET CMP0074 NEW)

# All building options

option(BOTCRAFT_USE_OPENGL_GUI "Activate if you want to use OpenGL renderer" OFF)
if(BOTCRAFT_USE_OPENGL_GUI)
    option(BOTCRAFT_USE_IMGUI "Activate if you want to use display information on screen with ImGui" OFF)
endif()
option(BOTCRAFT_COMPRESSION "Activate if compression is enabled on the server" ON)
option(BOTCRAFT_ENCRYPTION "Activate if you want to connect to a server in online mode" ON)
option(BOTCRAFT_BUILD_EXAMPLES "Set to compile examples with the library" ON)
option(BOTCRAFT_BUILD_TESTS "Activate if you want to build tests" OFF)
option(BOTCRAFT_WINDOWS_BETTER_SLEEP "Set to use better thread sleep on Windows" OFF)

option(BOTCRAFT_FORCE_LOCAL_ZLIB "Set to true to force using a local install of zlib even if already present on the system" OFF)
option(BOTCRAFT_FORCE_LOCAL_OPENSSL "Set to true to force using a local install of openssl even if already present on the system" OFF)
option(BOTCRAFT_FORCE_LOCAL_GLFW "Set to true to force using a local install of glfw even if already present on the system" OFF)
option(BOTCRAFT_FORCE_LOCAL_GLAD "Set to true to force using a local install of glad even if already present on the system" OFF)
option(BOTCRAFT_FORCE_LOCAL_CATCH "Set to true to force using a local install of catch2 even if already present on the system" OFF)
option(BOTCRAFT_DOWNLOAD_MC_ASSETS "Download Minecraft client and copy assets next to custom ones" ON)

set(BOTCRAFT_OUTPUT_DIR "${CMAKE_SOURCE_DIR}" CACHE PATH "Base output build path")

# Version selection stuffs
set(GAME_VERSION "latest" CACHE STRING "Each version of the game uses a specific protocol. Make sure this matches the version of your server.")
set(GameVersionValues "1.12.2;1.13;1.13.1;1.13.2;1.14;1.14.1;1.14.2;1.14.3;1.14.4;1.15;1.15.1;1.15.2;1.16;1.16.1;1.16.2;1.16.3;1.16.4;1.16.5;1.17;1.17.1;1.18;1.18.1;1.18.2;1.19;1.19.1;1.19.2;latest")
set(ProtocolVersionValues "340;393;401;404;477;480;485;490;498;573;575;578;735;736;751;753;754;754;755;756;757;757;758;759;760;760")
set(ClientURLs "https://launcher.mojang.com/v1/objects/0f275bc1547d01fa5f56ba34bdc87d981ee12daf/client.jar;https://launcher.mojang.com/v1/objects/c0b970952cdd279912da384cdbfc0c26e6c6090b/client.jar;https://launcher.mojang.com/v1/objects/8de235e5ec3a7fce168056ea395d21cbdec18d7c/client.jar;https://launcher.mojang.com/v1/objects/30bfe37a8db404db11c7edf02cb5165817afb4d9/client.jar;https://launcher.mojang.com/v1/objects/7a762a59345c13af7d87111207a93f5a8607f6c0/client.jar;https://launcher.mojang.com/v1/objects/55ba86ddcbc3579397f41910463ffd4056e1e523/client.jar;https://launcher.mojang.com/v1/objects/ca6c5a139045967229975c0c0b7f93e78b4314c2/client.jar;https://launcher.mojang.com/v1/objects/af100b34ec7ef2b8b9cf7775b544d21d690dddec/client.jar;https://launcher.mojang.com/v1/objects/8c325a0c5bd674dd747d6ebaa4c791fd363ad8a9/client.jar;https://launcher.mojang.com/v1/objects/7b07fd09d1e3aae1bc7a1304fedc73bfe5d81800/client.jar;https://launcher.mojang.com/v1/objects/8b11614bea9293592a947ea8f4fd72981ea66677/client.jar;https://launcher.mojang.com/v1/objects/e3f78cd16f9eb9a52307ed96ebec64241cc5b32d/client.jar;https://launcher.mojang.com/v1/objects/228fdf45541c4c2fe8aec4f20e880cb8fcd46621/client.jar;https://launcher.mojang.com/v1/objects/c9abbe8ee4fa490751ca70635340b7cf00db83ff/client.jar;https://launcher.mojang.com/v1/objects/653e97a2d1d76f87653f02242d243cdee48a5144/client.jar;https://launcher.mojang.com/v1/objects/1321521b2caf934f7fc9665aab7e059a7b2bfcdf/client.jar;https://launcher.mojang.com/v1/objects/1952d94a0784e7abda230aae6a1e8fc0522dba99/client.jar;https://launcher.mojang.com/v1/objects/37fd3c903861eeff3bc24b71eed48f828b5269c8/client.jar;https://launcher.mojang.com/v1/objects/1cf89c77ed5e72401b869f66410934804f3d6f52/client.jar;https://launcher.mojang.com/v1/objects/8d9b65467c7913fcf6f5b2e729d44a1e00fde150/client.jar;https://launcher.mojang.com/v1/objects/d49eb6caed53d23927648c97451503442f9e26fd/client.jar;https://launcher.mojang.com/v1/objects/7e46fb47609401970e2818989fa584fd467cd036/client.jar;https://launcher.mojang.com/v1/objects/2e9a3e3107cca00d6bc9c97bf7d149cae163ef21/client.jar;https://launcher.mojang.com/v1/objects/c0898ec7c6a5a2eaa317770203a1554260699994/client.jar;https://piston-data.mojang.com/v1/objects/90d438c3e432add8848a9f9f368ce5a52f6bc4a7/client.jar;https://piston-data.mojang.com/v1/objects/055b30d860ead928cba3849ba920c88b6950b654/client.jar")
set_property(CACHE GAME_VERSION PROPERTY STRINGS ${GameVersionValues})

if(GAME_VERSION STREQUAL "latest")
    list(GET GameVersionValues -2 GAME_VERSION)
endif()
list(FIND GameVersionValues ${GAME_VERSION} game_version_index)
list(GET ProtocolVersionValues ${game_version_index} PROTOCOL_VERSION)
list(GET ClientURLs "${game_version_index}" VERSION_CLIENTURL)
message(STATUS "Selected game version: " ${GAME_VERSION} " || Protocol: " ${PROTOCOL_VERSION})

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/version.txt" ${GAME_VERSION})
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/protocol.txt" ${PROTOCOL_VERSION})

# Do all the asset related stuffs
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/assets.cmake")

# Add Asio
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/asio.cmake")

# Add nlohmann json
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/json.cmake")

# Add ZLIB
if(BOTCRAFT_COMPRESSION)
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/zlib.cmake")
endif(BOTCRAFT_COMPRESSION)

# Add OpenSSL
if(BOTCRAFT_ENCRYPTION)
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/openssl.cmake")
endif(BOTCRAFT_ENCRYPTION)

if(BOTCRAFT_USE_OPENGL_GUI)
    # Add OpenGL
    find_package(OpenGL REQUIRED)
    
    # Add glad
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/glad.cmake")
    
    #Add GLFW
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/glfw.cmake")
    
    # Add GLM
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/glm.cmake")
    
    # Add stb_image
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/stb_image.cmake")
    
    # Add rectpack2D
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/rectpack2D.cmake")
    
    if(BOTCRAFT_USE_IMGUI)
        # Add Dear Imgui
        include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/imgui.cmake")
    endif()
endif()

# Check pthreads
find_package(Threads)

add_subdirectory(protocolCraft)
add_subdirectory(botcraft)
if(BOTCRAFT_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()

# Add tests if enabled
if (BOTCRAFT_BUILD_TESTS)
    include(CTest)
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/catch2.cmake")
    add_subdirectory(tests)
endif()
