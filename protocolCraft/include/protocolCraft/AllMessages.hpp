#pragma once

#include <tuple>

// Handshaking serverbound
#include "protocolCraft/Messages/Handshaking/Serverbound/ServerboundClientIntentionPacket.hpp"


// Login serverbound
#include "protocolCraft/Messages/Login/Serverbound/ServerboundHelloPacket.hpp"
#include "protocolCraft/Messages/Login/Serverbound/ServerboundKeyPacket.hpp"

// Login clientbound
#include "protocolCraft/Messages/Login/Clientbound/ClientboundLoginDisconnectPacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundHelloPacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundGameProfilePacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundLoginCompressionPacket.hpp"

//Status Serverbound
#include "protocolCraft/Messages/Status/Serverbound/ServerboundPingRequestPacket.hpp"
#include "protocolCraft/Messages/Status/Serverbound/ServerboundStatusRequestPacket.hpp"

// Status Clientbound
#include "protocolCraft/Messages/Status/Clientbound/ClientboundPongResponsePacket.hpp"
#include "protocolCraft/Messages/Status/Clientbound/ClientboundStatusResponsePacket.hpp"

// Play serverbound
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientCommandPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPosRot.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundKeepAlivePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientInformationPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundAcceptTeleportationPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerActionPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCommandSuggestionPacket.hpp"
#if PROTOCOL_VERSION < 476
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEnchantItemPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerClickPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerClosePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCustomPayloadPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundInteractPacket.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPos.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketRot.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMoveVehiclePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPaddleBoatPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlaceRecipePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerAbilitiesPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerCommandPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerInputPacket.hpp"
#if PROTOCOL_VERSION < 737
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookUpdatePacket.hpp"
#else
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookSeenRecipePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookChangeSettingsPacket.hpp"
#endif

#include "protocolCraft/Messages/Play/Serverbound/ServerboundResourcePackPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSeenAdvancementsPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCarriedItemPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCreativeModeSlotPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSignUpdatePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSwingPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundTeleportToEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundUseItemOnPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundUseItemPacket.hpp"
#if PROTOCOL_VERSION > 388
#include "protocolCraft/Messages/Play/Serverbound/ServerboundBlockEntityTagQuery.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEntityTagQuery.hpp"
#endif
#if PROTOCOL_VERSION > 385
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEditBookPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPickItemPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRenameItemPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSelectTradePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetBeaconPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandBlockPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandMinecartPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetStructureBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 463
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChangeDifficultyPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundLockDifficultyPacket.hpp"
#endif
#if PROTOCOL_VERSION > 476
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerButtonClickPacket.hpp"
#endif
#if PROTOCOL_VERSION > 471
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetJigsawBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 711
#include "protocolCraft/Messages/Play/Serverbound/ServerboundJigsawGeneratePacket.hpp"
#endif
#if PROTOCOL_VERSION > 754
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketStatusOnly.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPongPacket.hpp"
#endif

// Play clientbound
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockUpdatePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChatPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChangeDifficultyPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDisconnectPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundForgetLevelChunkPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundKeepAlivePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLoginPacket.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketPos.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketPosRot.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketRot.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerPositionPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetHealthPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTeleportEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerAbilitiesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTimePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRespawnPacket.hpp"
#if PROTOCOL_VERSION > 404
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLightUpdatePacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockEntityDataPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoPacket.hpp"
#if PROTOCOL_VERSION > 493
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockBreakAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetSlotPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetContentPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundOpenScreenPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetCarriedItemPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddExperienceOrbPacket.hpp"
#if PROTOCOL_VERSION < 721
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddGlobalEntityPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddMobPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddPaintingPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddPlayerPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAnimatePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAwardStatsPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockDestructionPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBossEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCommandSuggestionsPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerClosePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetDataPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCooldownPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomPayloadPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomSoundPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundEntityEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundExplodePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundGameEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelParticlesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMapItemDataPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveVehiclePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundOpenSignEditorPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlaceGhostRecipePacket.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatPacket.hpp"
#endif
#if PROTOCOL_VERSION < 461
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUseBedPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRecipePacket.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntitiesPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveMobEffectPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRotateHeadPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSelectAdvancementsTabPacket.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetCameraPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetDisplayObjectivePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityDataPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityLinkPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityMotionPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetEquipmentPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetExperiencePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetObjectivePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetPassengersPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetPlayerTeamPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetScorePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetDefaultSpawnPositionPacket.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTitlesPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSoundPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTabListPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTakeItemEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAdvancementsPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAttributesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateMobEffectPacket.hpp"
#if PROTOCOL_VERSION > 344
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCommandsPacket.hpp"
#endif
#if PROTOCOL_VERSION > 388
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTagQueryPacket.hpp"
#endif
#if PROTOCOL_VERSION > 351
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerLookAtPacket.hpp"
#endif
#if PROTOCOL_VERSION > 342
#include "protocolCraft/Messages/Play/Clientbound/ClientboundStopSoundPacket.hpp"
#endif
#if PROTOCOL_VERSION > 347
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateRecipesPacket.hpp"
#endif
#if PROTOCOL_VERSION > 348
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateTagsPacket.hpp"
#endif
#if PROTOCOL_VERSION > 451
#include "protocolCraft/Messages/Play/Clientbound/ClientboundHorseScreenOpenPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMerchantOffersPacket.hpp"
#endif
#if PROTOCOL_VERSION > 450
#include "protocolCraft/Messages/Play/Clientbound/ClientboundOpenBookPacket.hpp"
#endif
#if PROTOCOL_VERSION > 471
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheCenterPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheRadiusPacket.hpp"
#endif
#if PROTOCOL_VERSION > 440
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSoundEntityPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddVibrationSignalPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundClearTitlesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundInitializeBorderPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPingPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatEndPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatEnterPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatKillPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetActionBarTextPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderCenterPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderLerpSizePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderSizePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderWarningDelayPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderWarningDistancePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetSubtitleTextPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTitleTextPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTitlesAnimationPacket.hpp"
#endif


namespace ProtocolCraft
{
    using AllMessages = std::tuple <
        // Handshaking serverbound
        ServerboundClientIntentionPacket,


        // Login serverbound
        ServerboundHelloPacket,
        ServerboundKeyPacket,

        // Login clientbound
        ClientboundLoginDisconnectPacket,
        ClientboundHelloPacket,
        ClientboundGameProfilePacket,
        ClientboundLoginCompressionPacket,

        // Status serverbound
        ServerboundStatusRequestPacket,
        ServerboundPingRequestPacket,

        // Status clientbound
        ClientboundStatusResponsePacket,
        ClientboundPongResponsePacket,


        // Play serverbound
        ServerboundSeenAdvancementsPacket,
        ServerboundSwingPacket,
        ServerboundChatPacket,
        ServerboundContainerClickPacket,
#if PROTOCOL_VERSION > 476
        ServerboundContainerButtonClickPacket,
#endif
        ServerboundClientInformationPacket,
        ServerboundClientCommandPacket,
        ServerboundContainerClosePacket,
#if PROTOCOL_VERSION < 755
        ServerboundContainerAckPacket,
#endif
        ServerboundPlaceRecipePacket,
        ServerboundSetCreativeModeSlotPacket,
#if PROTOCOL_VERSION > 385
        ServerboundEditBookPacket,
#endif
#if PROTOCOL_VERSION < 476
        ServerboundEnchantItemPacket,
#endif
        ServerboundPlayerCommandPacket,
#if PROTOCOL_VERSION > 711
        ServerboundJigsawGeneratePacket,
#endif
        ServerboundSetCarriedItemPacket,
        ServerboundInteractPacket,
        ServerboundKeepAlivePacket,
#if PROTOCOL_VERSION > 463
        ServerboundLockDifficultyPacket,
#endif
#if PROTOCOL_VERSION > 385
        ServerboundRenameItemPacket,
        ServerboundPickItemPacket,
#endif
        ServerboundPlayerAbilitiesPacket,
        ServerboundUseItemOnPacket,
        ServerboundPlayerActionPacket,
        ServerboundMovePlayerPacketRot,
#if PROTOCOL_VERSION < 755
        ServerboundMovePlayerPacket,
#endif
        ServerboundMovePlayerPacketPos,
        ServerboundMovePlayerPacketPosRot,
        ServerboundCustomPayloadPacket,
#if PROTOCOL_VERSION > 388
        ServerboundBlockEntityTagQuery,
        ServerboundEntityTagQuery,
#endif
#if PROTOCOL_VERSION < 736
        ServerboundRecipeBookUpdatePacket,
#else
        ServerboundRecipeBookSeenRecipePacket,
        ServerboundRecipeBookChangeSettingsPacket,
#endif
        ServerboundResourcePackPacket,
#if PROTOCOL_VERSION > 385
        ServerboundSelectTradePacket,
        ServerboundSetBeaconPacket,
#endif
#if PROTOCOL_VERSION > 463
        ServerboundChangeDifficultyPacket,
#endif
        ServerboundTeleportToEntityPacket,
        ServerboundPaddleBoatPacket,
        ServerboundPlayerInputPacket,
        ServerboundCommandSuggestionPacket,
        ServerboundAcceptTeleportationPacket,
#if PROTOCOL_VERSION > 385
        ServerboundSetCommandBlockPacket,
        ServerboundSetCommandMinecartPacket,
#endif
#if PROTOCOL_VERSION > 471
        ServerboundSetJigsawBlockPacket,
#endif
        ServerboundSignUpdatePacket,
#if PROTOCOL_VERSION > 385
        ServerboundSetStructureBlockPacket,
#endif
        ServerboundUseItemPacket,
        ServerboundMoveVehiclePacket,
#if PROTOCOL_VERSION > 754
        ServerboundMovePlayerPacketStatusOnly,
        ServerboundPongPacket,
#endif

        // Play clientbound
        ClientboundUpdateAdvancementsPacket,
        ClientboundSetEntityLinkPacket,
        ClientboundBlockEventPacket,
        ClientboundBlockDestructionPacket,
        ClientboundBlockUpdatePacket,
        ClientboundBossEventPacket,
        ClientboundSetCameraPacket,
        ClientboundContainerClosePacket,
        ClientboundTakeItemEntityPacket,
#if PROTOCOL_VERSION < 755
        ClientboundPlayerCombatPacket,
        ClientboundRemoveEntitiesPacket,
#endif
#if PROTOCOL_VERSION > 345
        ClientboundCommandsPacket,
#endif
#if PROTOCOL_VERSION > 347
        ClientboundUpdateRecipesPacket,
#endif
#if PROTOCOL_VERSION > 351
        ClientboundPlayerLookAtPacket,
#endif
        ClientboundChangeDifficultyPacket,
        ClientboundMapItemDataPacket,
        ClientboundSectionBlocksUpdatePacket,
#if PROTOCOL_VERSION < 755
        ClientboundContainerAckPacket,
#endif
        ClientboundGameEventPacket,
        ClientboundPlaceGhostRecipePacket,
        ClientboundDisconnectPacket,
        ClientboundSetDisplayObjectivePacket,
        ClientboundForgetLevelChunkPacket,
        ClientboundKeepAlivePacket,
        ClientboundCustomSoundPacket,
#if PROTOCOL_VERSION > 388
        ClientboundTagQueryPacket,
#endif
        ClientboundOpenSignEditorPacket,
#if PROTOCOL_VERSION > 451
        ClientboundHorseScreenOpenPacket,
#endif
#if PROTOCOL_VERSION > 450
        ClientboundOpenBookPacket,
#endif
        ClientboundLevelChunkPacket,
        ClientboundLoginPacket,
        ClientboundLevelEventPacket, 
#if PROTOCOL_VERSION < 755
        ClientboundMoveEntityPacket,
#endif
        ClientboundAnimatePacket,
        ClientboundSetEquipmentPacket,
        ClientboundUpdateMobEffectPacket,
        ClientboundRotateHeadPacket,
        ClientboundMoveEntityPacketPos,
        ClientboundMoveEntityPacketPosRot,
        ClientboundMoveEntityPacketRot,
        ClientboundSetEntityDataPacket,
        ClientboundUpdateAttributesPacket,
#if PROTOCOL_VERSION > 450
        ClientboundSoundEntityPacket,
#endif
        ClientboundEntityEventPacket,
        ClientboundSetEntityMotionPacket,
        ClientboundExplodePacket,
        ClientboundLevelParticlesPacket,
        ClientboundPlayerPositionPacket,
        ClientboundSetHealthPacket,
        ClientboundTeleportEntityPacket,
        ClientboundPlayerAbilitiesPacket,
        ClientboundSetTimePacket,
        ClientboundChatPacket,
        ClientboundRespawnPacket,
#if PROTOCOL_VERSION > 404
        ClientboundLightUpdatePacket,
#endif
#if PROTOCOL_VERSION > 493
        ClientboundBlockBreakAckPacket,
#endif
        ClientboundBlockEntityDataPacket,
        ClientboundPlayerInfoPacket,
        ClientboundTabListPacket,
        ClientboundCustomPayloadPacket,
        ClientboundRemoveMobEffectPacket,
        ClientboundResourcePackPacket,
        ClientboundSetObjectivePacket,
        ClientboundSelectAdvancementsTabPacket,
        ClientboundSetExperiencePacket,
        ClientboundContainerSetSlotPacket,
        ClientboundCooldownPacket,
        ClientboundSetPassengersPacket,
        ClientboundSoundPacket,
        ClientboundAddExperienceOrbPacket,
#if PROTOCOL_VERSION < 721
        ClientboundAddGlobalEntityPacket,
#endif
        ClientboundAddMobPacket,
        ClientboundAddEntityPacket,
        ClientboundAddPaintingPacket,
        ClientboundAddPlayerPacket,
        ClientboundSetDefaultSpawnPositionPacket,
        ClientboundAwardStatsPacket,
#if PROTOCOL_VERSION > 342
        ClientboundStopSoundPacket,
#endif
#if PROTOCOL_VERSION > 348
        ClientboundUpdateTagsPacket,
#endif
        ClientboundCommandSuggestionsPacket,
        ClientboundSetPlayerTeamPacket,
#if PROTOCOL_VERSION < 755
        ClientboundSetTitlesPacket,
#endif
#if PROTOCOL_VERSION < 461
        ClientboundUseBedPacket,
#endif
#if PROTOCOL_VERSION > 451
        ClientboundMerchantOffersPacket,
#endif
        ClientboundRecipePacket,
        ClientboundSetScorePacket,
#if PROTOCOL_VERSION > 471
        ClientboundSetChunkCacheCenterPacket,
        ClientboundSetChunkCacheRadiusPacket,
#endif
        ClientboundMoveVehiclePacket,
        ClientboundContainerSetContentPacket,
        ClientboundContainerSetDataPacket,
        ClientboundOpenScreenPacket,
        ClientboundSetCarriedItemPacket,
#if PROTOCOL_VERSION < 755
        ClientboundSetBorderPacket,
#endif
#if PROTOCOL_VERSION > 754
        ClientboundAddVibrationSignalPacket,
        ClientboundClearTitlesPacket,
        ClientboundInitializeBorderPacket,
        ClientboundPingPacket,
        ClientboundPlayerCombatEndPacket,
        ClientboundPlayerCombatEnterPacket,
        ClientboundPlayerCombatKillPacket,
        ClientboundRemoveEntityPacket,
        ClientboundSetActionBarTextPacket,
        ClientboundSetBorderCenterPacket,
        ClientboundSetBorderLerpSizePacket,
        ClientboundSetBorderSizePacket,
        ClientboundSetBorderWarningDelayPacket,
        ClientboundSetBorderWarningDistancePacket,
        ClientboundSetSubtitleTextPacket,
        ClientboundSetTitleTextPacket,
        ClientboundSetTitlesAnimationPacket
#endif
    > ;
} //ProtocolCraft