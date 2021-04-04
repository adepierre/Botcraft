project(protocolCraft)

set(protocolCraft_PUBLIC_HDR
    include/protocolCraft/AllMessages.hpp
    include/protocolCraft/BaseMessage.hpp 
    include/protocolCraft/BinaryReadWrite.hpp
    include/protocolCraft/enums.hpp
    include/protocolCraft/GenericHandler.hpp
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
    
    include/protocolCraft/Messages/Status/Serverbound/Request.hpp
    include/protocolCraft/Messages/Status/Serverbound/Ping.hpp
    include/protocolCraft/Messages/Status/Clientbound/Response.hpp
    include/protocolCraft/Messages/Status/Clientbound/Pong.hpp
    
    include/protocolCraft/Messages/Play/Serverbound/AdvancementTab.hpp
    include/protocolCraft/Messages/Play/Serverbound/AnimationServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/ChatMessageServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/ClickWindow.hpp
    include/protocolCraft/Messages/Play/Serverbound/ClickWindowButton.hpp
    include/protocolCraft/Messages/Play/Serverbound/ClientSettings.hpp
    include/protocolCraft/Messages/Play/Serverbound/ClientStatus.hpp
    include/protocolCraft/Messages/Play/Serverbound/CloseWindowServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/ConfirmTransactionServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/CraftRecipeRequest.hpp
    include/protocolCraft/Messages/Play/Serverbound/CreativeInventoryAction.hpp
    include/protocolCraft/Messages/Play/Serverbound/EditBook.hpp
    include/protocolCraft/Messages/Play/Serverbound/EnchantItem.hpp
    include/protocolCraft/Messages/Play/Serverbound/EntityAction.hpp
    include/protocolCraft/Messages/Play/Serverbound/GenerateStructure.hpp
    include/protocolCraft/Messages/Play/Serverbound/HeldItemChangeServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/InteractEntity.hpp
    include/protocolCraft/Messages/Play/Serverbound/KeepAliveServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/LockDifficulty.hpp
    include/protocolCraft/Messages/Play/Serverbound/NameItem.hpp
    include/protocolCraft/Messages/Play/Serverbound/PickItem.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerMovement.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerPosition.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerAbilitiesServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerBlockPlacement.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerDigging.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerLook.hpp
    include/protocolCraft/Messages/Play/Serverbound/PlayerPositionAndLookServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/TabCompleteServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/PluginMessageServerbound.hpp
    include/protocolCraft/Messages/Play/Serverbound/QueryBlockNBT.hpp
    include/protocolCraft/Messages/Play/Serverbound/QueryEntityNBT.hpp
    include/protocolCraft/Messages/Play/Serverbound/ResourcePackStatus.hpp
    include/protocolCraft/Messages/Play/Serverbound/RecipeBookData.hpp
    include/protocolCraft/Messages/Play/Serverbound/Spectate.hpp
    include/protocolCraft/Messages/Play/Serverbound/SelectTrade.hpp
    include/protocolCraft/Messages/Play/Serverbound/SetBeaconEffect.hpp
    include/protocolCraft/Messages/Play/Serverbound/SetDifficulty.hpp
    include/protocolCraft/Messages/Play/Serverbound/SetDisplayedRecipe.hpp
    include/protocolCraft/Messages/Play/Serverbound/SetRecipeBookState.hpp
    include/protocolCraft/Messages/Play/Serverbound/SteerBoat.hpp
    include/protocolCraft/Messages/Play/Serverbound/SteerVehicle.hpp
    include/protocolCraft/Messages/Play/Serverbound/TeleportConfirm.hpp
    include/protocolCraft/Messages/Play/Serverbound/UpdateCommandBlock.hpp
    include/protocolCraft/Messages/Play/Serverbound/UpdateCommandBlockMinecart.hpp
    include/protocolCraft/Messages/Play/Serverbound/UpdateJigsawBlock.hpp
    include/protocolCraft/Messages/Play/Serverbound/UpdateSign.hpp
    include/protocolCraft/Messages/Play/Serverbound/UpdateStructureBlock.hpp
    include/protocolCraft/Messages/Play/Serverbound/UseItem.hpp
    include/protocolCraft/Messages/Play/Serverbound/VehicleMoveServerbound.hpp
    
    include/protocolCraft/Messages/Play/Clientbound/AcknowledgePlayerDigging.hpp
    include/protocolCraft/Messages/Play/Clientbound/Advancements.hpp
    include/protocolCraft/Messages/Play/Clientbound/AttachEntity.hpp
    include/protocolCraft/Messages/Play/Clientbound/BlockAction.hpp
    include/protocolCraft/Messages/Play/Clientbound/BlockBreakAnimation.hpp
    include/protocolCraft/Messages/Play/Clientbound/BlockChange.hpp
    include/protocolCraft/Messages/Play/Clientbound/BossBar.hpp
    include/protocolCraft/Messages/Play/Clientbound/Camera.hpp
    include/protocolCraft/Messages/Play/Clientbound/ChatMessageClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/ChangeGameState.hpp
    include/protocolCraft/Messages/Play/Clientbound/ChunkData.hpp
    include/protocolCraft/Messages/Play/Clientbound/CloseWindowClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/CollectItem.hpp
    include/protocolCraft/Messages/Play/Clientbound/ConfirmTransactionClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/CombatEvent.hpp
    include/protocolCraft/Messages/Play/Clientbound/CraftRecipeResponse.hpp
    include/protocolCraft/Messages/Play/Clientbound/DeclareCommands.hpp
    include/protocolCraft/Messages/Play/Clientbound/DeclareRecipes.hpp
    include/protocolCraft/Messages/Play/Clientbound/DestroyEntities.hpp
    include/protocolCraft/Messages/Play/Clientbound/DisconnectPlay.hpp
    include/protocolCraft/Messages/Play/Clientbound/DisplayScoreboard.hpp
    include/protocolCraft/Messages/Play/Clientbound/Effect.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityAnimationClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityEffect.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityEquipment.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityHeadLook.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityLook.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityLookAndRelativeMove.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityMetadata.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityMovement.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityProperties.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityRelativeMove.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntitySoundEffect.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityStatus.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityTeleport.hpp
    include/protocolCraft/Messages/Play/Clientbound/EntityVelocity.hpp
    include/protocolCraft/Messages/Play/Clientbound/Explosion.hpp
    include/protocolCraft/Messages/Play/Clientbound/FacePlayer.hpp
    include/protocolCraft/Messages/Play/Clientbound/HeldItemChangeClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/JoinGame.hpp
    include/protocolCraft/Messages/Play/Clientbound/KeepAliveClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/MapData.hpp
    include/protocolCraft/Messages/Play/Clientbound/MultiBlockChange.hpp
    include/protocolCraft/Messages/Play/Clientbound/NamedSoundEffect.hpp
    include/protocolCraft/Messages/Play/Clientbound/NBTQueryResponse.hpp
    include/protocolCraft/Messages/Play/Clientbound/OpenBook.hpp
    include/protocolCraft/Messages/Play/Clientbound/OpenWindow.hpp
    include/protocolCraft/Messages/Play/Clientbound/OpenHorseWindow.hpp
    include/protocolCraft/Messages/Play/Clientbound/OpenSignEditor.hpp
    include/protocolCraft/Messages/Play/Clientbound/PlayerAbilitiesClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/Particle.hpp
    include/protocolCraft/Messages/Play/Clientbound/PlayerInfo.hpp
    include/protocolCraft/Messages/Play/Clientbound/PlayerListHeaderAndFooter.hpp
    include/protocolCraft/Messages/Play/Clientbound/PlayerPositionAndLookClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/PluginMessageClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/RemoveEntityEffect.hpp
    include/protocolCraft/Messages/Play/Clientbound/Respawn.hpp
    include/protocolCraft/Messages/Play/Clientbound/RessourcePackSend.hpp
    include/protocolCraft/Messages/Play/Clientbound/ScoreboardObjective.hpp
    include/protocolCraft/Messages/Play/Clientbound/SelectAdvancementTab.hpp
    include/protocolCraft/Messages/Play/Clientbound/ServerDifficulty.hpp
    include/protocolCraft/Messages/Play/Clientbound/SetCooldown.hpp
    include/protocolCraft/Messages/Play/Clientbound/SetPassengers.hpp
    include/protocolCraft/Messages/Play/Clientbound/SoundEffect.hpp
    include/protocolCraft/Messages/Play/Clientbound/SpawnExperienceOrb.hpp
    include/protocolCraft/Messages/Play/Clientbound/SpawnGlobalEntity.hpp
    include/protocolCraft/Messages/Play/Clientbound/SpawnMob.hpp
    include/protocolCraft/Messages/Play/Clientbound/SpawnObject.hpp
    include/protocolCraft/Messages/Play/Clientbound/SpawnPainting.hpp
    include/protocolCraft/Messages/Play/Clientbound/SpawnPlayer.hpp
    include/protocolCraft/Messages/Play/Clientbound/SpawnPosition.hpp
    include/protocolCraft/Messages/Play/Clientbound/Statistics.hpp
    include/protocolCraft/Messages/Play/Clientbound/StopSound.hpp
    include/protocolCraft/Messages/Play/Clientbound/TabCompleteClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/Teams.hpp
    include/protocolCraft/Messages/Play/Clientbound/TimeUpdate.hpp
    include/protocolCraft/Messages/Play/Clientbound/Title.hpp
    include/protocolCraft/Messages/Play/Clientbound/UnloadChunk.hpp
    include/protocolCraft/Messages/Play/Clientbound/UnlockRecipes.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateBlockEntity.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateHealth.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateLight.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateScore.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateViewPosition.hpp
    include/protocolCraft/Messages/Play/Clientbound/UpdateViewDistance.hpp
    include/protocolCraft/Messages/Play/Clientbound/UseBed.hpp
    include/protocolCraft/Messages/Play/Clientbound/SetExperience.hpp
    include/protocolCraft/Messages/Play/Clientbound/SetSlot.hpp
    include/protocolCraft/Messages/Play/Clientbound/Tags.hpp
    include/protocolCraft/Messages/Play/Clientbound/TradeList.hpp
    include/protocolCraft/Messages/Play/Clientbound/VehicleMoveClientbound.hpp
    include/protocolCraft/Messages/Play/Clientbound/WindowItems.hpp
    include/protocolCraft/Messages/Play/Clientbound/WindowProperty.hpp
    include/protocolCraft/Messages/Play/Clientbound/WorldBorder.hpp
    
    include/protocolCraft/Types/Advancement.hpp
    include/protocolCraft/Types/AdvancementDisplay.hpp
    include/protocolCraft/Types/AdvancementProgress.hpp
    include/protocolCraft/Types/Chat.hpp
    include/protocolCraft/Types/CriterionProgress.hpp
    include/protocolCraft/Types/EntityModifierData.hpp
    include/protocolCraft/Types/EntityProperty.hpp
    include/protocolCraft/Types/MapIcon.hpp
    include/protocolCraft/Types/NetworkPosition.hpp
    include/protocolCraft/Types/PlayerProperty.hpp
    include/protocolCraft/Types/PlayerInformation.hpp
    include/protocolCraft/Types/Record.hpp
    include/protocolCraft/Types/Slot.hpp
    include/protocolCraft/Types/BlockEntityTag.hpp
    include/protocolCraft/Types/Trade.hpp
    
    include/protocolCraft/Types/CommandNode/CommandNode.hpp
    include/protocolCraft/Types/CommandNode/BrigadierProperty.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyDouble.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyEntity.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyFloat.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyInteger.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyNone.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyRange.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyScoreHolder.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyString.hpp
        
    include/protocolCraft/Types/Recipes/Recipe.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeData.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataBlasting.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataCampfireCooking.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataNone.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataShaped.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataShapeless.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataSmelting.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataSmithing.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataSmoking.hpp
    include/protocolCraft/Types/Recipes/RecipeTypeDataStoneCutting.hpp
    include/protocolCraft/Types/Recipes/Ingredient.hpp
    
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
    src/BaseMessage.cpp
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
    src/Types/CommandNode/BrigadierProperty.cpp
    src/Types/Recipes/RecipeTypeData.cpp
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
set_property(TARGET protocolCraft PROPERTY POSITION_INDEPENDENT_CODE ON)
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
