cmake_minimum_required(VERSION 3.19)

project(Botcraft)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Export DLL symbols on Windows
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
cmake_policy(SET CMP0074 NEW)

# All cmake options
option(BOTCRAFT_USE_OPENGL_GUI "Activate if you want to use OpenGL renderer" OFF)
option(BOTCRAFT_USE_IMGUI "Activate if you want to use display information on screen with ImGui" OFF)
option(BOTCRAFT_COMPRESSION "Activate if compression is enabled on the server" ON)
option(BOTCRAFT_ENCRYPTION "Activate if you want to connect to a server in online mode" ON)
option(BOTCRAFT_BUILD_EXAMPLES "Set to compile examples with the library" ON)
option(BOTCRAFT_BUILD_TESTS "Activate if you want to build tests" OFF)
option(BOTCRAFT_BUILD_TESTS_ONLINE "Activate if you want to enable additional on server tests (requires Java)" OFF)
option(BOTCRAFT_WINDOWS_BETTER_SLEEP "Set to true to use better thread sleep on Windows" ON)
option(BOTCRAFT_USE_PRECOMPILED_HEADERS "Set to true to precompile botcraft headers, reducing compilation time with MSVC and Clang, ignored on GCC" ON)
option(BOTCRAFT_BUILD_DOC "Build documentation (requires Doxygen)" ON)

option(BOTCRAFT_FORCE_LOCAL_ZLIB "Set to true to force using a local install of zlib even if already present on the system" OFF)
option(BOTCRAFT_FORCE_LOCAL_OPENSSL "Set to true to force using a local install of openssl even if already present on the system" OFF)
option(BOTCRAFT_FORCE_LOCAL_GLFW "Set to true to force using a local install of glfw even if already present on the system" OFF)
option(BOTCRAFT_FORCE_LOCAL_GLAD "Set to true to force using a local install of glad even if already present on the system" OFF)
option(BOTCRAFT_FORCE_LOCAL_CATCH "Set to true to force using a local install of catch2 even if already present on the system" OFF)
option(BOTCRAFT_INSTALL_MC_ASSETS "Install Minecraft assets next to custom ones" ON)

# Only change them if you *really* know what you are doing, not supported and very untested, will probably break something
option(PROTOCOLCRAFT_STATIC "If ON, will build protocolcraft as a static library instead of a dynamic one" OFF)
mark_as_advanced(PROTOCOLCRAFT_STATIC)
option(BOTCRAFT_STATIC "If ON, will build botcraft as a static library instead of a dynamic one" OFF)
mark_as_advanced(BOTCRAFT_STATIC)

set(BOTCRAFT_OUTPUT_DIR "${CMAKE_SOURCE_DIR}" CACHE PATH "Base output build path")

# Version selection stuffs
set(BOTCRAFT_GAME_VERSION "latest" CACHE STRING "Each version of the game uses a specific protocol. Make sure this matches the version of your server.")
set(GameVersionValues "1.12.2;1.13;1.13.1;1.13.2;1.14;1.14.1;1.14.2;1.14.3;1.14.4;1.15;1.15.1;1.15.2;1.16;1.16.1;1.16.2;1.16.3;1.16.4;1.16.5;1.17;1.17.1;1.18;1.18.1;1.18.2;1.19;1.19.1;1.19.2;1.19.3;1.19.4;1.20;1.20.1;1.20.2;1.20.3;1.20.4;1.20.5;1.20.6;1.21;1.21.1;1.21.2;1.21.3;1.21.4;1.21.5;1.21.6;1.21.7;1.21.8;1.21.9;1.21.10;1.21.11;latest")
set(ProtocolVersionValues "340;393;401;404;477;480;485;490;498;573;575;578;735;736;751;753;754;754;755;756;757;757;758;759;760;760;761;762;763;763;764;765;765;766;766;767;767;768;768;769;770;771;772;772;773;773;774")
set_property(CACHE BOTCRAFT_GAME_VERSION PROPERTY STRINGS ${GameVersionValues})

if(BOTCRAFT_GAME_VERSION STREQUAL "latest")
    list(GET GameVersionValues -2 BOTCRAFT_GAME_VERSION)
endif()

list(FIND GameVersionValues ${BOTCRAFT_GAME_VERSION} game_version_index)
list(GET ProtocolVersionValues ${game_version_index} PROTOCOL_VERSION)
message(STATUS "Selected game version: " ${BOTCRAFT_GAME_VERSION} " || Protocol: " ${PROTOCOL_VERSION})

# Automatically retrieve client/server URLs for the selected game version
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/mc_urls.cmake")
get_mc_version_urls(${BOTCRAFT_GAME_VERSION})

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/version.txt" ${BOTCRAFT_GAME_VERSION})
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/protocol.txt" ${PROTOCOL_VERSION})

# Installation stuff
include(GNUInstallDirs)

# Do all the assets related stuffs
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/assets.cmake")

# Add Asio
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/asio.cmake")

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

    if(BOTCRAFT_BUILD_TESTS_ONLINE AND BOTCRAFT_COMPRESSION)
        # Add subprocess
        include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/subprocess.cmake")

        # Check if JRE is present to run the test server
        if(BOTCRAFT_GAME_VERSION VERSION_LESS "1.17")
            find_package(Java 8 QUIET COMPONENTS Runtime)
        elseif(BOTCRAFT_GAME_VERSION VERSION_LESS "1.20.5")
            find_package(Java 17 QUIET COMPONENTS Runtime)
        else()
            find_package(Java 21 QUIET COMPONENTS Runtime)
        endif()

        if(NOT Java_FOUND)
            message(WARNING "Java not found. Online tests will be built, but won't be able to run on this machine. You can disable online tests by setting BOTCRAFT_BUILD_TESTS_ONLINE to OFF")
        endif()

        # Make sure server.jar is present
        download_mc_server(${VERSION_SERVER_URL} "${BOTCRAFT_OUTPUT_DIR}/bin/test_server_files/server_jars/server_${BOTCRAFT_GAME_VERSION}.jar")
    elseif(BOTCRAFT_BUILD_TESTS_ONLINE)
        message(WARNING "Online tests require BOTCRAFT_COMPRESSION")
    endif()

    add_subdirectory(tests)
endif()

# Add doc generation if enabled
if (BOTCRAFT_BUILD_DOC)
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/doxygen.cmake")
endif(BOTCRAFT_BUILD_DOC)

target_link_libraries(2_ChatCommandExample -fsanitize=address,undefined)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
