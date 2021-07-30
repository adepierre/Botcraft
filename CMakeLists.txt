cmake_minimum_required(VERSION 3.4)

project(Botcraft)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# All building options

option(BOTCRAFT_USE_OPENGL_GUI "Activate if you want to use OpenGL renderer" OFF)
if(BOTCRAFT_USE_OPENGL_GUI)
    option(BOTCRAFT_USE_IMGUI "Activate if you want to use display information on screen with ImGui" OFF)
endif()
option(BOTCRAFT_COMPRESSION "Activate if compression is enabled on the server" ON)
option(BOTCRAFT_ENCRYPTION "Activate if you want to connect to a server in online mode" ON)
option(BOTCRAFT_BUILD_EXAMPLES "Set to compile examples with the library" ON)
option(BOTCRAFT_INSTALL_ASSETS "Set to copy used assets to installation folder" ON)

# Version selection stuffs
set(GAME_VERSION "latest" CACHE STRING "Each version of the game uses a specific protocol. Make sure this matches the version of your server.")
set(GameVersionValues "1.12.2;1.13;1.13.1;1.13.2;1.14;1.14.1;1.14.2;1.14.3;1.14.4;1.15;1.15.1;1.15.2;1.16;1.16.1;1.16.2;1.16.3;1.16.4;1.16.5;1.17;1.17.1;latest")
set(ProtocolVersionValues "340;393;401;404;477;480;485;490;498;573;575;578;735;736;751;753;754;754;755;756")
set(ClientURLs "https://launcher.mojang.com/v1/objects/0f275bc1547d01fa5f56ba34bdc87d981ee12daf/client.jar;https://launcher.mojang.com/v1/objects/c0b970952cdd279912da384cdbfc0c26e6c6090b/client.jar;https://launcher.mojang.com/v1/objects/8de235e5ec3a7fce168056ea395d21cbdec18d7c/client.jar;https://launcher.mojang.com/v1/objects/30bfe37a8db404db11c7edf02cb5165817afb4d9/client.jar;https://launcher.mojang.com/v1/objects/7a762a59345c13af7d87111207a93f5a8607f6c0/client.jar;https://launcher.mojang.com/v1/objects/55ba86ddcbc3579397f41910463ffd4056e1e523/client.jar;https://launcher.mojang.com/v1/objects/ca6c5a139045967229975c0c0b7f93e78b4314c2/client.jar;https://launcher.mojang.com/v1/objects/af100b34ec7ef2b8b9cf7775b544d21d690dddec/client.jar;https://launcher.mojang.com/v1/objects/8c325a0c5bd674dd747d6ebaa4c791fd363ad8a9/client.jar;https://launcher.mojang.com/v1/objects/7b07fd09d1e3aae1bc7a1304fedc73bfe5d81800/client.jar;https://launcher.mojang.com/v1/objects/8b11614bea9293592a947ea8f4fd72981ea66677/client.jar;https://launcher.mojang.com/v1/objects/e3f78cd16f9eb9a52307ed96ebec64241cc5b32d/client.jar;https://launcher.mojang.com/v1/objects/228fdf45541c4c2fe8aec4f20e880cb8fcd46621/client.jar;https://launcher.mojang.com/v1/objects/c9abbe8ee4fa490751ca70635340b7cf00db83ff/client.jar;https://launcher.mojang.com/v1/objects/653e97a2d1d76f87653f02242d243cdee48a5144/client.jar;https://launcher.mojang.com/v1/objects/1321521b2caf934f7fc9665aab7e059a7b2bfcdf/client.jar;https://launcher.mojang.com/v1/objects/1952d94a0784e7abda230aae6a1e8fc0522dba99/client.jar;https://launcher.mojang.com/v1/objects/37fd3c903861eeff3bc24b71eed48f828b5269c8/client.jar;https://launcher.mojang.com/v1/objects/1cf89c77ed5e72401b869f66410934804f3d6f52/client.jar;https://launcher.mojang.com/v1/objects/8d9b65467c7913fcf6f5b2e729d44a1e00fde150/client.jar")
set_property(CACHE GAME_VERSION PROPERTY STRINGS ${GameVersionValues})

if(GAME_VERSION STREQUAL "latest")
    list(GET GameVersionValues -2 GAME_VERSION)
endif()
    list(FIND GameVersionValues ${GAME_VERSION} game_version_index)
    list(GET ProtocolVersionValues ${game_version_index} PROTOCOL_VERSION)
message(STATUS "Selected game version: " ${GAME_VERSION} " || Protocol: " ${PROTOCOL_VERSION})

# Check if the minecraft assets folder already exists
# If not, download the client and extract the assets
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft)
    list(GET ClientURLs ${game_version_index} VERSION_CLIENTURL)
    message(STATUS "Downloading assets for version " ${GAME_VERSION} " from " ${VERSION_CLIENTURL} "...")
    file(DOWNLOAD ${VERSION_CLIENTURL} ${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/client.jar)
    message(STATUS "Extracting assets...")
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/)
    execute_process(COMMAND "cmake" "-E" "tar" "xfz" "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/client.jar" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/assets/minecraft/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/)
    message(STATUS "Removing temp folder")
    file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/temp)
endif()

set(ASSET_DIR ../Assets/${GAME_VERSION})

# Add Asio
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/asio.cmake)

# Add picoJson
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/picoJson.cmake)

# Add ZLIB
if(BOTCRAFT_COMPRESSION)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/zlib.cmake)
endif(BOTCRAFT_COMPRESSION)

# Add OpenSSL
if(BOTCRAFT_ENCRYPTION)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/openssl.cmake)
endif(BOTCRAFT_ENCRYPTION)

if(BOTCRAFT_USE_OPENGL_GUI)
    # Add OpenGL
    find_package(OpenGL REQUIRED)
    
    # Add glad
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glad.cmake)
    
    #Add GLFW
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glfw.cmake)
    
    # Add GLM
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glm.cmake)
    
    # Add stb_image
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/stb_image.cmake)
    
    # Add rectpack2D
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/rectpack2D.cmake)
    
    if(BOTCRAFT_USE_IMGUI)
        # Add Dear Imgui
        include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/imgui.cmake)
    endif()
endif()

# Check pthreads
find_package(Threads)

add_subdirectory(protocolCraft)
add_subdirectory(botcraft)
if(BOTCRAFT_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()
