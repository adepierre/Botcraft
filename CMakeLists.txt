cmake_minimum_required(VERSION 3.4)

project(Botcraft)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

option(BOTCRAFT_USE_OPENGL_GUI "Activate if you want to use OpenGL renderer" OFF)
if(BOTCRAFT_USE_OPENGL_GUI)
	option(BOTCRAFT_USE_IMGUI "Activate if you want to use display information on screen with ImGui" OFF)
endif()
option(BOTCRAFT_USE_ZLIB "Use Zlib if compression is enabled on the server" OFF)

# Version selection stuffs
set(GAME_VERSION "1.12.2" CACHE STRING "Each version of the game uses a specific protocol. Make sure this matches the version of your server.")
set(GameVersionValues "1.12.2;1.13;1.13.1;1.13.2;1.14;1.14.1;1.14.2;1.14.3;1.14.4;Other")
set(ProtocolVersionValues "340;393;401;404;477;480;485;490;498;-1")
set(ClientURLs "https://launcher.mojang.com/v1/objects/0f275bc1547d01fa5f56ba34bdc87d981ee12daf/client.jar;https://launcher.mojang.com/v1/objects/c0b970952cdd279912da384cdbfc0c26e6c6090b/client.jar;https://launcher.mojang.com/v1/objects/8de235e5ec3a7fce168056ea395d21cbdec18d7c/client.jar;https://launcher.mojang.com/v1/objects/30bfe37a8db404db11c7edf02cb5165817afb4d9/client.jar;https://launcher.mojang.com/v1/objects/7a762a59345c13af7d87111207a93f5a8607f6c0/client.jar;https://launcher.mojang.com/v1/objects/55ba86ddcbc3579397f41910463ffd4056e1e523/client.jar;https://launcher.mojang.com/v1/objects/ca6c5a139045967229975c0c0b7f93e78b4314c2/client.jar;https://launcher.mojang.com/v1/objects/af100b34ec7ef2b8b9cf7775b544d21d690dddec/client.jar;https://launcher.mojang.com/v1/objects/8c325a0c5bd674dd747d6ebaa4c791fd363ad8a9/client.jar")
set_property(CACHE GAME_VERSION PROPERTY STRINGS ${GameVersionValues})

if(GAME_VERSION STREQUAL "Other")
    message(SEND_ERROR "You must specify an actual value for GAME_VERSION")
else()
	list(FIND GameVersionValues ${GAME_VERSION} game_version_index)
	list(GET ProtocolVersionValues ${game_version_index} PROTOCOL_VERSION)
	message(STATUS "Selected game version: " ${GAME_VERSION} " || Protocol: " ${PROTOCOL_VERSION})
    
    # Check if the minecraft assets folder already exists
    # If not, download the client and extract the assets
    if(NOT EXISTS ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft)
        list(GET ClientURLs ${game_version_index} VERSION_CLIENTURL)
        message(STATUS "Downloading assets for version " ${GAME_VERSION} " from " ${VERSION_CLIENTURL} "...")
        file(DOWNLOAD ${VERSION_CLIENTURL} ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/client.jar)
        message(STATUS "Extracting assets...")
        file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/)
        execute_process(COMMAND "cmake" "-E" "tar" "xfz" "${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/client.jar" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/)
        file(COPY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/assets/minecraft/ DESTINATION ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/)
        message(STATUS "Removing temp folder")
        file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/temp)
    endif()
    
endif()

option(BOTCRAFT_BUILD_EXAMPLES "Set to compile examples with the library" ON)
option(BOTCRAFT_INSTALL_ASSETS "Set to copy used assets to installation folder" ON)

set(ASSET_DIR ../Assets/${GAME_VERSION})

# Add Boost
find_package(Boost COMPONENTS system date_time regex thread)

# Add picoJson
include(${CMAKE_SOURCE_DIR}/cmake/picoJson.cmake)

# Add ZLIB
if(BOTCRAFT_USE_ZLIB)
	include(${CMAKE_SOURCE_DIR}/cmake/zlib.cmake)
endif(BOTCRAFT_USE_ZLIB)

if(BOTCRAFT_USE_OPENGL_GUI)
	# Add OpenGL
	find_package(OpenGL REQUIRED)
	
	# Add glad
	include(${CMAKE_SOURCE_DIR}/cmake/glad.cmake)
	
	#Add GLFW
	include(${CMAKE_SOURCE_DIR}/cmake/glfw.cmake)
	
	# Add GLM
	include(${CMAKE_SOURCE_DIR}/cmake/glm.cmake)
	
	# Add stb_image
	include(${CMAKE_SOURCE_DIR}/cmake/stb_image.cmake)
	
	if(BOTCRAFT_USE_IMGUI)
		# Add Dear Imgui
		include(${CMAKE_SOURCE_DIR}/cmake/imgui.cmake)
	endif()
endif()

add_subdirectory(botcraft)
if(BOTCRAFT_BUILD_EXAMPLES)
	add_subdirectory(Examples)
endif()
