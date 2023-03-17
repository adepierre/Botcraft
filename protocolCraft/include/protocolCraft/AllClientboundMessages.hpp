#pragma once

#include <tuple>
#include "protocolCraft/Utilities/TupleCat.hpp"

// Login clientbound
#if PROTOCOL_VERSION > 340
#include "protocolCraft/Messages/Login/Clientbound/ClientboundCustomQueryPacket.hpp"
#endif
#include "protocolCraft/Messages/Login/Clientbound/ClientboundLoginDisconnectPacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundHelloPacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundGameProfilePacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundLoginCompressionPacket.hpp"

// Status Clientbound
#include "protocolCraft/Messages/Status/Clientbound/ClientboundPongResponsePacket.hpp"
#include "protocolCraft/Messages/Status/Clientbound/ClientboundStatusResponsePacket.hpp"

// Play clientbound
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockUpdatePacket.hpp"
#if PROTOCOL_VERSION < 759
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChatPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChangeDifficultyPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDisconnectPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundForgetLevelChunkPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundKeepAlivePacket.hpp"
#if PROTOCOL_VERSION < 757
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkPacket.hpp"
#endif
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
#if PROTOCOL_VERSION < 761
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoPacket.hpp"
#endif
#if PROTOCOL_VERSION > 493 && PROTOCOL_VERSION < 759
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
#if PROTOCOL_VERSION < 759
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddMobPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddPaintingPacket.hpp"
#endif
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
#if PROTOCOL_VERSION < 761
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomSoundPacket.hpp"
#endif
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
#if PROTOCOL_VERSION == 755
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntityPacket.hpp"
#else
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
#if PROTOCOL_VERSION < 759
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddVibrationSignalPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundClearTitlesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundInitializeBorderPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPingPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatEndPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatEnterPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatKillPacket.hpp"
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
#if PROTOCOL_VERSION > 756
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkWithLightPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetSimulationDistancePacket.hpp"
#endif
#if PROTOCOL_VERSION > 758
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockChangedAckPacket.hpp"
#if PROTOCOL_VERSION < 761
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChatPreviewPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerChatPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundServerDataPacket.hpp"
#if PROTOCOL_VERSION < 761
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetDisplayChatPreviewPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSystemChatPacket.hpp"
#endif
#if PROTOCOL_VERSION > 759
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomChatCompletionsPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDeleteChatPacket.hpp"
#if PROTOCOL_VERSION < 761
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerChatHeaderPacket.hpp"
#endif
#endif
#if PROTOCOL_VERSION > 760
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDisguisedChatPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoRemovePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoUpdatePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp"
#endif
#if PROTOCOL_VERSION > 761
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBundlePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChunksBiomesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDamageEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundHurtAnimationPacket.hpp"
#endif

namespace ProtocolCraft
{
    using AllClientboundLoginPacket = std::tuple<
#if PROTOCOL_VERSION > 340
        ClientboundCustomQueryPacket,
#endif
        ClientboundLoginDisconnectPacket,
        ClientboundHelloPacket,
        ClientboundGameProfilePacket,
        ClientboundLoginCompressionPacket
    >;

    using AllClientboundStatusPacket = std::tuple<
        ClientboundStatusResponsePacket,
        ClientboundPongResponsePacket
    >;

    using AllClientboundPlayPacket = std::tuple<
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
#endif
#if PROTOCOL_VERSION == 755
        ClientboundRemoveEntityPacket,
#else
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
#if PROTOCOL_VERSION < 761
        ClientboundCustomSoundPacket,
#endif
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
#if PROTOCOL_VERSION < 757
        ClientboundLevelChunkPacket,
#endif
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
#if PROTOCOL_VERSION < 759
        ClientboundChatPacket,
#endif
        ClientboundRespawnPacket,
#if PROTOCOL_VERSION > 404
        ClientboundLightUpdatePacket,
#endif
#if PROTOCOL_VERSION > 493 && PROTOCOL_VERSION < 759
        ClientboundBlockBreakAckPacket,
#endif
        ClientboundBlockEntityDataPacket,
#if PROTOCOL_VERSION < 761
        ClientboundPlayerInfoPacket,
#endif
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
#if PROTOCOL_VERSION < 759
        ClientboundAddMobPacket,
#endif
        ClientboundAddEntityPacket,
#if PROTOCOL_VERSION < 759
        ClientboundAddPaintingPacket,
#endif
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
#if PROTOCOL_VERSION < 755
        ClientboundSetBorderPacket,
#endif
#if PROTOCOL_VERSION > 754
#if PROTOCOL_VERSION < 759
        ClientboundAddVibrationSignalPacket,
#endif
        ClientboundClearTitlesPacket,
        ClientboundInitializeBorderPacket,
        ClientboundPingPacket,
        ClientboundPlayerCombatEndPacket,
        ClientboundPlayerCombatEnterPacket,
        ClientboundPlayerCombatKillPacket,
        ClientboundSetActionBarTextPacket,
        ClientboundSetBorderCenterPacket,
        ClientboundSetBorderLerpSizePacket,
        ClientboundSetBorderSizePacket,
        ClientboundSetBorderWarningDelayPacket,
        ClientboundSetBorderWarningDistancePacket,
        ClientboundSetSubtitleTextPacket,
        ClientboundSetTitleTextPacket,
        ClientboundSetTitlesAnimationPacket,
#endif
#if PROTOCOL_VERSION > 756
        ClientboundLevelChunkWithLightPacket,
        ClientboundSetSimulationDistancePacket,
#endif
#if PROTOCOL_VERSION > 758
        ClientboundBlockChangedAckPacket,
#if PROTOCOL_VERSION < 761
        ClientboundChatPreviewPacket,
#endif
        ClientboundPlayerChatPacket,
        ClientboundServerDataPacket,
#if PROTOCOL_VERSION < 761
        ClientboundSetDisplayChatPreviewPacket,
#endif
        ClientboundSystemChatPacket,
#endif
#if PROTOCOL_VERSION > 759
        ClientboundCustomChatCompletionsPacket,
        ClientboundDeleteChatPacket,
#if PROTOCOL_VERSION < 761
        ClientboundPlayerChatHeaderPacket,
#endif
#endif
#if PROTOCOL_VERSION > 760
        ClientboundDisguisedChatPacket,
        ClientboundPlayerInfoRemovePacket,
        ClientboundPlayerInfoUpdatePacket,
        ClientboundUpdateEnabledFeaturesPacket,
#endif
#if PROTOCOL_VERSION > 761
        ClientboundBundlePacket,
        ClientboundChunksBiomesPacket,
        ClientboundDamageEventPacket,
        ClientboundHurtAnimationPacket,
#endif
        ClientboundSetCarriedItemPacket
    >;

    using AllClientboundMessages = Internal::tuple_cat_t<
        AllClientboundLoginPacket,
        AllClientboundStatusPacket,
        AllClientboundPlayPacket
    >;
} //ProtocolCraft
