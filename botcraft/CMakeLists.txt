project(botcraft)

set(botcraft_PUBLIC_HDR 
	include/botcraft/Game/AABB.hpp
	include/botcraft/Game/AssetsManager.hpp
	include/botcraft/Game/BaseClient.hpp
	include/botcraft/Game/Biome.hpp
	include/botcraft/Game/Block.hpp
	include/botcraft/Game/Blockstate.hpp
	include/botcraft/Game/Chunk.hpp
	include/botcraft/Game/Enums.hpp
	include/botcraft/Game/InterfaceClient.hpp
	include/botcraft/Game/Model.hpp
	include/botcraft/Game/OtherPlayer.hpp
	include/botcraft/Game/Player.hpp
	include/botcraft/Game/Section.hpp
	include/botcraft/Game/Vector3.hpp
	include/botcraft/Game/World.hpp
	include/botcraft/Network/BinaryReadWrite.hpp
	include/botcraft/Protocol/AllMessages.hpp
	include/botcraft/Protocol/BaseMessage.hpp
	include/botcraft/Protocol/Handler.hpp
	include/botcraft/Protocol/Message.hpp
	include/botcraft/Protocol/MessageFactory.hpp
	include/botcraft/Protocol/Type.hpp
	include/botcraft/NBT/NBT.hpp
	include/botcraft/NBT/Tag.hpp
	include/botcraft/NBT/TagEnd.hpp
	include/botcraft/NBT/TagByte.hpp
	include/botcraft/NBT/TagShort.hpp
	include/botcraft/NBT/TagInt.hpp
	include/botcraft/NBT/TagLong.hpp
	include/botcraft/NBT/TagFloat.hpp
	include/botcraft/NBT/TagDouble.hpp
	include/botcraft/NBT/TagByteArray.hpp
	include/botcraft/NBT/TagString.hpp
	include/botcraft/NBT/TagList.hpp
	include/botcraft/NBT/TagCompound.hpp
	include/botcraft/NBT/TagIntArray.hpp
	include/botcraft/NBT/TagLongArray.hpp
)

set(botcraft_PRIVATE_HDR
	private_include/botcraft/Network/Compression.hpp
	private_include/botcraft/Network/TCP_Com.hpp
)

set(botcraft_SRC 
	src/Game/AABB.cpp
	src/Game/AssetsManager.cpp
	src/Game/BaseClient.cpp
	src/Game/Biome.cpp
	src/Game/Block.cpp
	src/Game/Blockstate.cpp
	src/Game/Chunk.cpp
	src/Game/InterfaceClient.cpp
	src/Game/Model.cpp
	src/Game/OtherPlayer.cpp
	src/Game/Player.cpp
	src/Game/World.cpp
	src/Network/BinaryReadWrite.cpp
	src/Network/Compression.cpp
	src/Network/TCP_Com.cpp
	src/NBT/NBT.cpp
	src/NBT/Tag.cpp
	src/NBT/TagEnd.cpp
	src/NBT/TagByte.cpp
	src/NBT/TagShort.cpp
	src/NBT/TagInt.cpp
	src/NBT/TagLong.cpp
	src/NBT/TagFloat.cpp
	src/NBT/TagDouble.cpp
	src/NBT/TagByteArray.cpp
	src/NBT/TagString.cpp
	src/NBT/TagList.cpp
	src/NBT/TagCompound.cpp
	src/NBT/TagIntArray.cpp
	src/NBT/TagLongArray.cpp
)

# Get the protocol files. As there are a lot of them I do not list them manually here (shame)
file(GLOB_RECURSE PROTOCOL_HDR_FILES RELATIVE "${PROJECT_SOURCE_DIR}" "include/botcraft/Protocol/Messages/*.hpp")
list(APPEND botcraft_PUBLIC_HDR ${PROTOCOL_HDR_FILES})
file(GLOB_RECURSE PROTOCOL_HDR_FILES RELATIVE "${PROJECT_SOURCE_DIR}" "include/botcraft/Protocol/Types/*.hpp")
list(APPEND botcraft_PUBLIC_HDR ${PROTOCOL_HDR_FILES})

file(GLOB_RECURSE PROTOCOL_SRC_FILES RELATIVE "${PROJECT_SOURCE_DIR}" "src/Protocol/Messages/*.cpp")
list(APPEND botcraft_SRC ${PROTOCOL_SRC_FILES})
file(GLOB_RECURSE PROTOCOL_SRC_FILES RELATIVE "${PROJECT_SOURCE_DIR}" "src/Protocol/Types/*.cpp")
list(APPEND botcraft_SRC ${PROTOCOL_SRC_FILES})

if(BOTCRAFT_USE_OPENGL_GUI)
	list(APPEND botcraft_PUBLIC_HDR
			include/botcraft/Renderer/CubeWorldRenderer.hpp
			include/botcraft/Renderer/Face.hpp
			include/botcraft/Renderer/Transformation.hpp
			)
			
	list(APPEND botcraft_PRIVATE_HDR
			private_include/botcraft/Renderer/Atlas.hpp
			private_include/botcraft/Renderer/Camera.hpp
			private_include/botcraft/Renderer/Chunk.hpp
			private_include/botcraft/Renderer/ImageSaver.hpp
			private_include/botcraft/Renderer/Shader.hpp
			private_include/botcraft/Renderer/TransparentChunk.hpp
			)
			
	list(APPEND botcraft_SRC
			src/Renderer/Atlas.cpp
			src/Renderer/Camera.cpp
			src/Renderer/Chunk.cpp
			src/Renderer/CubeWorldRenderer.cpp
			src/Renderer/Face.cpp
			src/Renderer/ImageSaver.cpp
			src/Renderer/Shader.cpp
			src/Renderer/Transformation.cpp
			src/Renderer/TransparentChunk.cpp
			)
endif(BOTCRAFT_USE_OPENGL_GUI)


# To have a nice files structure in Visual Studio
if(MSVC)
    foreach(source IN LISTS botcraft_PUBLIC_HDR)
        get_filename_component(source_path_header "${source}" PATH)
        string(REPLACE "include/botcraft" "Header Files/public" source_path_header "${source_path_header}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path_header}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
	
	foreach(source IN LISTS botcraft_PRIVATE_HDR)
        get_filename_component(source_path_header "${source}" PATH)
        string(REPLACE "private_include/botcraft" "Header Files/private" source_path_header "${source_path_header}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path_header}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()

    foreach(source IN LISTS botcraft_SRC)
        get_filename_component(source_path "${source}" PATH)
        string(REPLACE "src" "Source Files" source_path "${source_path}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
endif()

add_library(botcraft SHARED ${botcraft_SRC} ${botcraft_PUBLIC_HDR} ${botcraft_PRIVATE_HDR})
set_property(TARGET botcraft PROPERTY CXX_STANDARD 11)
set_target_properties(botcraft PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(botcraft PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")

if(MSVC)
	# To avoid having folder for each configuration when building with Visual
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/lib")
else()
	set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
	set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
	set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
endif(MSVC)

# Set version header
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/botcraft/Version.hpp)

# Add include folders
target_include_directories(botcraft 
	PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:include>		
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private_include>
		)
		
target_compile_definitions(botcraft PRIVATE ASSETS_PATH="${ASSET_DIR}")

# Add picoJson
target_link_libraries(botcraft PRIVATE picoJson)

# Add Asio
target_link_libraries(botcraft PRIVATE asio)
target_compile_definitions(botcraft PRIVATE ASIO_STANDALONE)

# Add graphical dependencies
if(BOTCRAFT_USE_OPENGL_GUI)
    target_link_libraries(botcraft PRIVATE glfw glad glm OpenGL::GL stb_image)
	if(BOTCRAFT_USE_IMGUI)
		target_link_libraries(botcraft PRIVATE imgui)
		target_compile_definitions(botcraft PUBLIC USE_IMGUI=1)
	endif()
	target_compile_definitions(botcraft PUBLIC USE_GUI=1)
endif(BOTCRAFT_USE_OPENGL_GUI)

if(BOTCRAFT_USE_ZLIB)
    target_link_libraries(botcraft PRIVATE ZLIB::ZLIB)
    target_compile_definitions(botcraft PUBLIC USE_ZLIB=1)
endif(BOTCRAFT_USE_ZLIB)

# Installation stuff
include(GNUInstallDirs)

install(TARGETS botcraft
	EXPORT botcraft-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
	
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/botcraft
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES 
	${CMAKE_CURRENT_BINARY_DIR}/include/botcraft/Version.hpp
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/botcraft)
	
install(EXPORT botcraft-targets
	FILE botcraft-targets.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/botcraft
)
	
include(CMakePackageConfigHelpers)

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/botcraft-config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake/botcraft-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/botcraft
)
	
install(
	FILES 
		${CMAKE_CURRENT_BINARY_DIR}/cmake/botcraft-config.cmake
	DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/botcraft
)

export(EXPORT botcraft-targets
	FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/botcraft-targets.cmake
)

if(BOTCRAFT_INSTALL_ASSETS)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/custom
		DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets/${GAME_VERSION}
	)
	
	# Check for assets, copy only needed files to install folder
	if(EXISTS ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft)
		if(EXISTS ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/blockstates)
			install(DIRECTORY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/blockstates
				DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets/${GAME_VERSION}/minecraft
			)
		else()
			message(WARNING "Can't find assets folder ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/blockstates")
		endif()
		if(EXISTS ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/models/block)
			install(DIRECTORY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/models/block
				DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets/${GAME_VERSION}/minecraft/models
			)
		else()
			message(WARNING "Can't find assets folder ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/models/block")
		endif()
		if(EXISTS ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/models/block)
			install(DIRECTORY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/models/block
				DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets/${GAME_VERSION}/minecraft/models
			)
		else()
			message(WARNING "Can't find assets folder ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/models/block")
		endif()
		
		if(BOTCRAFT_USE_OPENGL_GUI)
			if(EXISTS ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/blocks)
				install(DIRECTORY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/blocks
					DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets/${GAME_VERSION}/minecraft/textures
				)
            elseif(EXISTS ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/block)
                install(DIRECTORY ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/block
					DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets/${GAME_VERSION}/minecraft/textures
				)
			else()
				message(WARNING "Can't find assets folder ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/blocks or ${CMAKE_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/block")
			endif()
		endif()
	else()
		message(WARNING "Assets folder can't be found for selected game version.")
	endif()
endif()