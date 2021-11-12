project(botcraft)

set(botcraft_PUBLIC_HDR
    include/botcraft/AI/TemplatedBehaviourClient.hpp
    include/botcraft/AI/BehaviourClient.hpp
    include/botcraft/AI/BehaviourTree.hpp
    include/botcraft/AI/Blackboard.hpp
    include/botcraft/AI/SimpleBehaviourClient.hpp
    
    include/botcraft/AI/Tasks/AllTasks.hpp
    include/botcraft/AI/Tasks/BaseTasks.hpp
    include/botcraft/AI/Tasks/DigTask.hpp
    include/botcraft/AI/Tasks/InventoryTasks.hpp
    include/botcraft/AI/Tasks/PathfindingTask.hpp
    
    include/botcraft/Game/AABB.hpp
    include/botcraft/Game/Entities/Entity.hpp
    include/botcraft/Game/Entities/EntityManager.hpp
    include/botcraft/Game/Entities/LocalPlayer.hpp
    include/botcraft/Game/Entities/Player.hpp
    include/botcraft/Game/AssetsManager.hpp
    include/botcraft/Game/ManagersClient.hpp
    include/botcraft/Game/ConnectionClient.hpp
    include/botcraft/Game/World/Biome.hpp
    include/botcraft/Game/World/Block.hpp
    include/botcraft/Game/World/Blockstate.hpp
    include/botcraft/Game/World/Chunk.hpp
    include/botcraft/Game/Enums.hpp
    include/botcraft/Game/Model.hpp
    include/botcraft/Game/World/Section.hpp
    include/botcraft/Game/Vector3.hpp
    include/botcraft/Game/World/World.hpp
    include/botcraft/Game/Inventory/Window.hpp
    include/botcraft/Game/Inventory/InventoryManager.hpp
    include/botcraft/Game/Inventory/Item.hpp
    
    include/botcraft/Network/NetworkManager.hpp
    
    include/botcraft/Utilities/AsyncHandler.hpp
)

set(botcraft_PRIVATE_HDR
    private_include/botcraft/Network/Authentifier.hpp
    private_include/botcraft/Network/AESEncrypter.hpp
    private_include/botcraft/Network/Compression.hpp
    private_include/botcraft/Network/TCP_Com.hpp
    
    private_include/botcraft/Network/DNS/DNSMessage.hpp
    private_include/botcraft/Network/DNS/DNSQuestion.hpp
    private_include/botcraft/Network/DNS/DNSResourceRecord.hpp
    private_include/botcraft/Network/DNS/DNSSrvData.hpp
    
    private_include/botcraft/Utilities/StringUtilities.hpp
)

set(botcraft_SRC
    src/AI/BehaviourClient.cpp
    src/AI/SimpleBehaviourClient.cpp
    
    src/AI/Tasks/BaseTasks.cpp
    src/AI/Tasks/DigTask.cpp
    src/AI/Tasks/InventoryTasks.cpp
    src/AI/Tasks/PathfindingTask.cpp
    
    src/Game/AABB.cpp
    src/Game/AssetsManager.cpp
    src/Game/ManagersClient.cpp
    src/Game/ConnectionClient.cpp
    src/Game/Entities/Entity.cpp
    src/Game/Entities/EntityManager.cpp
    src/Game/Entities/LocalPlayer.cpp
    src/Game/Entities/Player.cpp
    src/Game/World/Biome.cpp
    src/Game/World/Block.cpp
    src/Game/World/Blockstate.cpp
    src/Game/World/Chunk.cpp
    src/Game/Model.cpp
    src/Game/World/World.cpp
    src/Game/Inventory/Window.cpp
    src/Game/Inventory/InventoryManager.cpp
    src/Game/Inventory/Item.cpp
    
    src/Network/Authentifier.cpp
    src/Network/AESEncrypter.cpp
    src/Network/Compression.cpp
    src/Network/NetworkManager.cpp
    src/Network/TCP_Com.cpp
    
    src/Utilities/StringUtilities.cpp
    src/Utilities/AsyncHandler.cpp
)

if(BOTCRAFT_USE_OPENGL_GUI)
    list(APPEND botcraft_PUBLIC_HDR
            include/botcraft/Renderer/RenderingManager.hpp
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
            private_include/botcraft/Renderer/WorldRenderer.hpp
            )
            
    list(APPEND botcraft_SRC
            src/Renderer/Atlas.cpp
            src/Renderer/Camera.cpp
            src/Renderer/Chunk.cpp
            src/Renderer/RenderingManager.cpp
            src/Renderer/Face.cpp
            src/Renderer/ImageSaver.cpp
            src/Renderer/Shader.cpp
            src/Renderer/Transformation.cpp
            src/Renderer/TransparentChunk.cpp
            src/Renderer/WorldRenderer.cpp
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
set_property(TARGET botcraft PROPERTY CXX_STANDARD 17)
set_target_properties(botcraft PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(botcraft PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")

if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/lib")
else()
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/lib")
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

# Add protocolCraft
target_link_libraries(botcraft PUBLIC protocolCraft)

# Add json
target_include_directories(botcraft 
    PUBLIC 
        $<BUILD_INTERFACE:${JSON_INCLUDE_DIR}>
)

# Add Asio
target_link_libraries(botcraft PRIVATE asio)
target_compile_definitions(botcraft PRIVATE ASIO_STANDALONE)

# Add threads support
target_link_libraries(botcraft PUBLIC Threads::Threads)

# Add graphical dependencies
if(BOTCRAFT_USE_OPENGL_GUI)
    target_link_libraries(botcraft PRIVATE glfw glad glm rectpack2D OpenGL::GL stb_image)
    if(BOTCRAFT_USE_IMGUI)
        target_link_libraries(botcraft PRIVATE imgui)
        target_compile_definitions(botcraft PUBLIC USE_IMGUI=1)
    endif()
    target_compile_definitions(botcraft PUBLIC USE_GUI=1)
endif(BOTCRAFT_USE_OPENGL_GUI)

if(BOTCRAFT_COMPRESSION)
    target_link_libraries(botcraft PRIVATE ZLIB::ZLIB)
    target_compile_definitions(botcraft PUBLIC USE_COMPRESSION=1)
endif(BOTCRAFT_COMPRESSION)

if(BOTCRAFT_ENCRYPTION)
    target_link_libraries(botcraft PRIVATE OpenSSL::SSL)
    target_link_libraries(botcraft PRIVATE OpenSSL::Crypto)
    target_compile_definitions(botcraft PRIVATE USE_ENCRYPTION=1)
endif(BOTCRAFT_ENCRYPTION)

# Installation stuff
include(GNUInstallDirs)

install(TARGETS botcraft
    EXPORT botcraft-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
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

# Copy json
install(DIRECTORY ${JSON_INCLUDE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

export(EXPORT botcraft-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/botcraft-targets.cmake
)

# Copy asset files into install binary folder
install(DIRECTORY ${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}
    DESTINATION ${CMAKE_INSTALL_BINDIR}/Assets
)