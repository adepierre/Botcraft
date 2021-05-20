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
    
    include/protocolCraft/Messages/Handshaking/Serverbound/ServerboundClientIntentionPacket.hpp
    
    
    include/protocolCraft/Messages/Login/Clientbound/ClientboundGameProfilePacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundHelloPacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundLoginCompressionPacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundLoginDisconnectPacket.hpp
    
    include/protocolCraft/Messages/Login/Serverbound/ServerboundHelloPacket.hpp
    include/protocolCraft/Messages/Login/Serverbound/ServerboundKeyPacket.hpp
    
    
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockBreakAckPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAdvancementsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityLinkPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockDestructionPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBossEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetCameraPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundChatPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundGameEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerClosePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTakeItemEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerAckPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlaceGhostRecipePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCommandsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateRecipesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntitiesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundDisconnectPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetDisplayObjectivePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLevelEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAnimatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateMobEffectPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetEquipmentPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRotateHeadPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketRot.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketPosRot.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAttributesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketPos.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSoundEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundEntityEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTeleportEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityMotionPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundExplodePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerLookAtPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetCarriedItemPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLoginPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundKeepAlivePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMapItemDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCustomSoundPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTagQueryPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundOpenBookPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundOpenScreenPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundHorseScreenOpenPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundOpenSignEditorPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerAbilitiesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLevelParticlesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTabListPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerPositionPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCustomPayloadPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRemoveMobEffectPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRespawnPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetObjectivePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSelectAdvancementsTabPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundChangeDifficultyPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCooldownPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetPassengersPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSoundPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddExperienceOrbPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddGlobalEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddMobPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddPaintingPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddPlayerPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetDefaultSpawnPositionPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAwardStatsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundStopSoundPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCommandSuggestionsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetPlayerTeamPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetTimePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetTitlesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundForgetLevelChunkPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRecipePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockEntityDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetHealthPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLightUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetScorePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheCenterPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheRadiusPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUseBedPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetExperiencePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetSlotPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateTagsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMerchantOffersPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveVehiclePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetContentPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderPacket.hpp
    
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSeenAdvancementsPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSwingPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChatPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundContainerClickPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundContainerButtonClickPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundClientInformationPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundClientCommandPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundContainerClosePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlaceRecipePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetCreativeModeSlotPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundEditBookPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundEnchantItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerCommandPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundJigsawGeneratePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetCarriedItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundInteractPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundKeepAlivePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundLockDifficultyPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundRenameItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPickItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPos.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerAbilitiesPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundUseItemOnPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerActionPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketRot.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPosRot.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundCommandSuggestionPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundCustomPayloadPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundBlockEntityTagQuery.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundEntityTagQuery.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundResourcePackPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundTeleportToEntityPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSelectTradePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetBeaconPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChangeDifficultyPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookSeenRecipePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookChangeSettingsPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPaddleBoatPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerInputPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundAcceptTeleportationPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandBlockPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandMinecartPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetJigsawBlockPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSignUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetStructureBlockPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundUseItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMoveVehiclePacket.hpp
    
    
    include/protocolCraft/Messages/Status/Clientbound/ClientboundPongResponsePacket.hpp
    include/protocolCraft/Messages/Status/Clientbound/ClientboundStatusResponsePacket.hpp
    
    include/protocolCraft/Messages/Status/Serverbound/ServerboundStatusRequestPacket.hpp
    include/protocolCraft/Messages/Status/Serverbound/ServerboundPingRequestPacket.hpp
    
    
    include/protocolCraft/Types/Advancement.hpp
    include/protocolCraft/Types/AdvancementDisplay.hpp
    include/protocolCraft/Types/AdvancementProgress.hpp
    include/protocolCraft/Types/Chat.hpp
    include/protocolCraft/Types/CriterionProgress.hpp
    include/protocolCraft/Types/EntityModifierData.hpp
    include/protocolCraft/Types/EntityProperty.hpp
    include/protocolCraft/Types/Identifier.hpp
    include/protocolCraft/Types/MapDecoration.hpp
    include/protocolCraft/Types/NetworkPosition.hpp
    include/protocolCraft/Types/PlayerProperty.hpp
    include/protocolCraft/Types/PlayerUpdate.hpp
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
    include/protocolCraft/Types/Recipes/RecipeBookSettings.hpp
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
