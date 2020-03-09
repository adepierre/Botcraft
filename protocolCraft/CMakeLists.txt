project(protocolCraft)

set(protocolCraft_PUBLIC_HDR
    include/protocolCraft/AllMessages.hpp
    include/protocolCraft/BaseMessage.hpp 
    include/protocolCraft/BinaryReadWrite.hpp
    include/protocolCraft/Handler.hpp
    include/protocolCraft/Message.hpp
    include/protocolCraft/MessageFactory.hpp
    include/protocolCraft/NetworkType.hpp
    
    include/protocolCraft/Messages/Handshaking/Serverbound/Handshake.hpp
    
    include/protocolCraft/Messages/Login/Serverbound/LoginStart.hpp
    include/protocolCraft/Messages/Login/Serverbound/EncryptionResponse.hpp
    include/protocolCraft/Messages/Login/Clientbound/DisconnectLogin.hpp
    include/protocolCraft/Messages/Login/Clientbound/EncryptionRequest.hpp
    include/protocolCraft/Messages/Login/Clientbound/LoginSuccess.hpp
    include/protocolCraft/Messages/Login/Clientbound/SetCompression.hpp
    
    include/protocolCraft/Messages/Play/Serverbound/ChatMessageServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/ClientSettings.hpp
    include/protocolCraft/Messages/Play/Serverbound/ClientStatus.hpp
    include/protocolCraft/Messages/Play/Serverbound/ConfirmTransactionServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/KeepAliveServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerDigging.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerPositionAndLookServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/TeleportConfirm.hpp
    include/protocolCraft/Messages/Play/Clientbound/AcknowledgePlayerDigging.hpp
    include/protocolCraft/Messages/Play/Clientbound/BlockChange.hpp
    include/protocolCraft/Messages/Play/Clientbound/ChatMessageClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/ChunkData.hpp
    include/protocolCraft/Messages/Play/Clientbound/ConfirmTransactionClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/DisconnectPlay.hpp
    include/protocolCraft/Messages/Play/Clientbound/Entity.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityLook.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityLookAndRelativeMove.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityRelativeMove.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityTeleport.hpp
    include/protocolCraft/Messages/Play/Clientbound/JoinGame.hpp
    include/protocolCraft/Messages/Play/Clientbound/KeepAliveClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/MultiBlockChange.hpp
    include/protocolCraft/Messages/Play/Clientbound/PlayerAbilitiesClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/PlayerInfo.hpp
    include/protocolCraft/Messages/Play/Clientbound/PlayerPositionAndLookClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/Respawn.hpp
    include/protocolCraft/Messages/Play/Clientbound/ServerDifficulty.hpp
    include/protocolCraft/Messages/Play/Clientbound/TimeUpdate.hpp
    include/protocolCraft/Messages/Play/Clientbound/UnloadChunk.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateBlockEntity.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateHealth.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateLight.hpp
    include/protocolCraft/Messages/Play/Clientbound/SetSlot.hpp
    include/protocolCraft/Messages/Play/Clientbound/WindowItems.hpp
    include/protocolCraft/Messages/Play/Clientbound/OpenWindow.hpp
    include/protocolCraft/Messages/Play/Clientbound/HeldItemChangeClientbound.hpp
    
    include/protocolCraft/Types/Chat.hpp
    include/protocolCraft/Types/NetworkPosition.hpp
    include/protocolCraft/Types/PlayerProperty.hpp
    include/protocolCraft/Types/PlayerInformation.hpp
    include/protocolCraft/Types/Record.hpp
    include/protocolCraft/Types/Slot.hpp
    
    include/protocolCraft/Types/NBT/NBT.hpp
    include/protocolCraft/Types/NBT/Tag.hpp
    include/protocolCraft/Types/NBT/TagEnd.hpp
    include/protocolCraft/Types/NBT/TagByte.hpp
    include/protocolCraft/Types/NBT/TagShort.hpp
    include/protocolCraft/Types/NBT/TagInt.hpp
    include/protocolCraft/Types/NBT/TagLong.hpp
    include/protocolCraft/Types/NBT/TagFloat.hpp
    include/protocolCraft/Types/NBT/TagDouble.hpp
    include/protocolCraft/Types/NBT/TagByteArray.hpp
    include/protocolCraft/Types/NBT/TagString.hpp
    include/protocolCraft/Types/NBT/TagList.hpp
    include/protocolCraft/Types/NBT/TagCompound.hpp
    include/protocolCraft/Types/NBT/TagIntArray.hpp
    include/protocolCraft/Types/NBT/TagLongArray.hpp
)

set(protocolCraft_SRC 
    src/BinaryReadWrite.cpp
    src/Types/Chat.cpp
    src/Types/NBT/NBT.cpp
    src/Types/NBT/Tag.cpp
    src/Types/NBT/TagEnd.cpp
    src/Types/NBT/TagByte.cpp
    src/Types/NBT/TagShort.cpp
    src/Types/NBT/TagInt.cpp
    src/Types/NBT/TagLong.cpp
    src/Types/NBT/TagFloat.cpp
    src/Types/NBT/TagDouble.cpp
    src/Types/NBT/TagByteArray.cpp
    src/Types/NBT/TagString.cpp
    src/Types/NBT/TagList.cpp
    src/Types/NBT/TagCompound.cpp
    src/Types/NBT/TagIntArray.cpp
    src/Types/NBT/TagLongArray.cpp
)

# To have a nice files structure in Visual Studio
if(MSVC)
    foreach(source IN LISTS protocolCraft_PUBLIC_HDR)
        get_filename_component(source_path_header "${source}" PATH)
        string(REPLACE "include/protocolCraft" "Header Files/public" source_path_header "${source_path_header}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path_header}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
    
    foreach(source IN LISTS protocolCraft_SRC)
        get_filename_component(source_path "${source}" PATH)
        string(REPLACE "src" "Source Files" source_path "${source_path}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
endif()

add_library(protocolCraft STATIC ${protocolCraft_SRC} ${protocolCraft_PUBLIC_HDR})
set_property(TARGET protocolCraft PROPERTY CXX_STANDARD 11)
set_target_properties(protocolCraft PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(protocolCraft PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")

if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/lib")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/lib")
else()
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
endif(MSVC)

# Set version
target_compile_definitions(protocolCraft PUBLIC PROTOCOL_VERSION=${PROTOCOL_VERSION})

# Add include folders
target_include_directories(protocolCraft 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

# Add picoJson
target_include_directories(protocolCraft 
    PUBLIC 
        $<BUILD_INTERFACE:${PICOJSON_INCLUDE_DIR}>
)

# Installation stuff
include(GNUInstallDirs)

install(TARGETS protocolCraft
    EXPORT protocolCraft-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
    
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/protocolCraft
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
    
install(EXPORT protocolCraft-targets
    FILE protocolCraft-targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/protocolCraft
)

# Copy picoJson
install(DIRECTORY ${PICOJSON_INCLUDE_DIR}
    DESTINATION ${CMAKE_INSTALL_PREFIX})

export(EXPORT protocolCraft-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/protocolCraft-targets.cmake
)
