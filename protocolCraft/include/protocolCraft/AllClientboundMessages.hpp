#pragma once

#include <tuple>
#include "protocolCraft/Utilities/TupleCat.hpp"

// Login clientbound
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Login/Clientbound/ClientboundCookieRequestPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Login/Clientbound/ClientboundCustomQueryPacket.hpp"
#endif
#include "protocolCraft/Messages/Login/Clientbound/ClientboundLoginDisconnectPacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundHelloPacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundGameProfilePacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundLoginCompressionPacket.hpp"

// Status Clientbound
#include "protocolCraft/Messages/Status/Clientbound/ClientboundPongResponsePacket.hpp"
#include "protocolCraft/Messages/Status/Clientbound/ClientboundStatusResponsePacket.hpp"

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
// Configuration Clientbound
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundCustomPayloadPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundDisconnectPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundFinishConfigurationPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundKeepAlivePacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundPingPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundRegistryDataPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundUpdateTagsPacket.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPopConfigurationPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPushConfigurationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundCookieRequestPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundResetChatPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundStoreCookiePacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundSelectKnownPacksPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundTransferPacket.hpp"
#endif

// Play clientbound
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockUpdatePacket.hpp"
#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChatPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChangeDifficultyPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp"
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDisconnectPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundForgetLevelChunkPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundKeepAlivePacket.hpp"
#if PROTOCOL_VERSION < 757 /* < 1.18 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLoginPacket.hpp"
#if PROTOCOL_VERSION < 755 /* < 1.17 */
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
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLightUpdatePacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockEntityDataPacket.hpp"
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoPacket.hpp"
#endif
#if PROTOCOL_VERSION > 493 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockBreakAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetSlotPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetContentPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundOpenScreenPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetCarriedItemPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddExperienceOrbPacket.hpp"
#if PROTOCOL_VERSION < 721 /* < 1.16 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddGlobalEntityPacket.hpp"
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddMobPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddPaintingPacket.hpp"
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddPlayerPacket.hpp"
#endif
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
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
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
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatPacket.hpp"
#endif
#if PROTOCOL_VERSION < 461 /* < 1.14 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUseBedPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRecipePacket.hpp"
#if PROTOCOL_VERSION == 755 /* 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntityPacket.hpp"
#else
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntitiesPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveMobEffectPacket.hpp"
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRotateHeadPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSelectAdvancementsTabPacket.hpp"
#if PROTOCOL_VERSION < 755 /* < 1.17 */
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
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTitlesPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSoundPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTabListPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTakeItemEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAdvancementsPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAttributesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateMobEffectPacket.hpp"
#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCommandsPacket.hpp"
#endif
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTagQueryPacket.hpp"
#endif
#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerLookAtPacket.hpp"
#endif
#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundStopSoundPacket.hpp"
#endif
#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateRecipesPacket.hpp"
#endif
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateTagsPacket.hpp"
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundHorseScreenOpenPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMerchantOffersPacket.hpp"
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundOpenBookPacket.hpp"
#endif
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheCenterPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheRadiusPacket.hpp"
#endif
#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSoundEntityPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#if PROTOCOL_VERSION < 759 /* < 1.19 */
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
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkWithLightPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetSimulationDistancePacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockChangedAckPacket.hpp"
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChatPreviewPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerChatPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundServerDataPacket.hpp"
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetDisplayChatPreviewPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSystemChatPacket.hpp"
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomChatCompletionsPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDeleteChatPacket.hpp"
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerChatHeaderPacket.hpp"
#endif
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDisguisedChatPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoRemovePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoUpdatePacket.hpp"
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp"
#endif
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBundlePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChunksBiomesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDamageEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundHurtAnimationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChunkBatchFinishedPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChunkBatchStartPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPongResponsePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundStartConfigurationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResetScorePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPopPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPushPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTickingStatePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTickingStepPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCookieRequestPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDebugSamplePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundProjectilePowerPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundStoreCookiePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTransferPacket.hpp"
#endif

namespace ProtocolCraft
{
    using AllClientboundLoginMessages = std::tuple<
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundCookieRequestLoginPacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ClientboundCustomQueryPacket,
#endif
        ClientboundLoginDisconnectPacket,
        ClientboundHelloPacket,
        ClientboundGameProfilePacket,
        ClientboundLoginCompressionPacket
    >;

    using AllClientboundStatusMessages = std::tuple<
        ClientboundStatusResponsePacket,
        ClientboundPongResponseStatusPacket
    >;

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    using AllClientboundConfigurationMessages = std::tuple<
        ClientboundCustomPayloadConfigurationPacket,
        ClientboundDisconnectConfigurationPacket,
        ClientboundFinishConfigurationPacket,
        ClientboundKeepAliveConfigurationPacket,
        ClientboundPingConfigurationPacket,
        ClientboundRegistryDataPacket,
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        ClientboundResourcePackConfigurationPacket,
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        ClientboundResourcePackPopConfigurationPacket,
        ClientboundResourcePackPushConfigurationPacket,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundCookieRequestConfigurationPacket,
        ClientboundResetChatPacket,
        ClientboundStoreCookieConfigurationPacket,
        ClientboundSelectKnownPacksPacket,
        ClientboundTransferConfigurationPacket,
#endif
        ClientboundUpdateEnabledFeaturesPacket,
        ClientboundUpdateTagsConfigurationPacket
    >;
#endif

    using AllClientboundPlayMessages = std::tuple<
        ClientboundUpdateAdvancementsPacket,
        ClientboundSetEntityLinkPacket,
        ClientboundBlockEventPacket,
        ClientboundBlockDestructionPacket,
        ClientboundBlockUpdatePacket,
        ClientboundBossEventPacket,
        ClientboundSetCameraPacket,
        ClientboundContainerClosePacket,
        ClientboundTakeItemEntityPacket,
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundPlayerCombatPacket,
#endif
#if PROTOCOL_VERSION == 755 /* 1.17 */
        ClientboundRemoveEntityPacket,
#else
        ClientboundRemoveEntitiesPacket,
#endif
#if PROTOCOL_VERSION > 345 /* > 1.12.2 */
        ClientboundCommandsPacket,
#endif
#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
        ClientboundUpdateRecipesPacket,
#endif
#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
        ClientboundPlayerLookAtPacket,
#endif
        ClientboundChangeDifficultyPacket,
        ClientboundMapItemDataPacket,
        ClientboundSectionBlocksUpdatePacket,
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundContainerAckPacket,
#endif
        ClientboundGameEventPacket,
        ClientboundPlaceGhostRecipePacket,
        ClientboundDisconnectPacket,
        ClientboundSetDisplayObjectivePacket,
        ClientboundForgetLevelChunkPacket,
        ClientboundKeepAlivePacket,
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundCustomSoundPacket,
#endif
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
        ClientboundTagQueryPacket,
#endif
        ClientboundOpenSignEditorPacket,
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
        ClientboundHorseScreenOpenPacket,
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
        ClientboundOpenBookPacket,
#endif
#if PROTOCOL_VERSION < 757 /* < 1.18 */
        ClientboundLevelChunkPacket,
#endif
        ClientboundLoginPacket,
        ClientboundLevelEventPacket,
#if PROTOCOL_VERSION < 755 /* < 1.17 */
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
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
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
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        ClientboundChatPacket,
#endif
        ClientboundRespawnPacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundLightUpdatePacket,
#endif
#if PROTOCOL_VERSION > 493 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        ClientboundBlockBreakAckPacket,
#endif
        ClientboundBlockEntityDataPacket,
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundPlayerInfoPacket,
#endif
        ClientboundTabListPacket,
        ClientboundCustomPayloadPacket,
        ClientboundRemoveMobEffectPacket,
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        ClientboundResourcePackPacket,
#endif
        ClientboundSetObjectivePacket,
        ClientboundSelectAdvancementsTabPacket,
        ClientboundSetExperiencePacket,
        ClientboundContainerSetSlotPacket,
        ClientboundCooldownPacket,
        ClientboundSetPassengersPacket,
        ClientboundSoundPacket,
        ClientboundAddExperienceOrbPacket,
#if PROTOCOL_VERSION < 721 /* < 1.16 */
        ClientboundAddGlobalEntityPacket,
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        ClientboundAddMobPacket,
#endif
        ClientboundAddEntityPacket,
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        ClientboundAddPaintingPacket,
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        ClientboundAddPlayerPacket,
#endif
        ClientboundSetDefaultSpawnPositionPacket,
        ClientboundAwardStatsPacket,
#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
        ClientboundStopSoundPacket,
#endif
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
        ClientboundUpdateTagsPacket,
#endif
        ClientboundCommandSuggestionsPacket,
        ClientboundSetPlayerTeamPacket,
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundSetTitlesPacket,
#endif
#if PROTOCOL_VERSION < 461 /* < 1.14 */
        ClientboundUseBedPacket,
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
        ClientboundMerchantOffersPacket,
#endif
        ClientboundRecipePacket,
        ClientboundSetScorePacket,
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
        ClientboundSetChunkCacheCenterPacket,
        ClientboundSetChunkCacheRadiusPacket,
#endif
        ClientboundMoveVehiclePacket,
        ClientboundContainerSetContentPacket,
        ClientboundContainerSetDataPacket,
        ClientboundOpenScreenPacket,
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundSetBorderPacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#if PROTOCOL_VERSION < 759 /* < 1.19 */
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
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        ClientboundLevelChunkWithLightPacket,
        ClientboundSetSimulationDistancePacket,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        ClientboundBlockChangedAckPacket,
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundChatPreviewPacket,
#endif
        ClientboundPlayerChatPacket,
        ClientboundServerDataPacket,
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundSetDisplayChatPreviewPacket,
#endif
        ClientboundSystemChatPacket,
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        ClientboundCustomChatCompletionsPacket,
        ClientboundDeleteChatPacket,
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundPlayerChatHeaderPacket,
#endif
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        ClientboundDisguisedChatPacket,
        ClientboundPlayerInfoRemovePacket,
        ClientboundPlayerInfoUpdatePacket,
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        ClientboundUpdateEnabledFeaturesPacket,
#endif
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ClientboundBundlePacket,
        ClientboundChunksBiomesPacket,
        ClientboundDamageEventPacket,
        ClientboundHurtAnimationPacket,
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ClientboundChunkBatchFinishedPacket,
        ClientboundChunkBatchStartPacket,
        ClientboundPongResponsePacket,
        ClientboundStartConfigurationPacket,
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        ClientboundResetScorePacket,
        ClientboundResourcePackPopPacket,
        ClientboundResourcePackPushPacket,
        ClientboundTickingStatePacket,
        ClientboundTickingStepPacket,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundCookieRequestPacket,
        ClientboundDebugSamplePacket,
        ClientboundProjectilePowerPacket,
        ClientboundStoreCookiePacket,
        ClientboundTransferPacket,
#endif
        ClientboundSetCarriedItemPacket
    >;

    using AllClientboundMessages = Internal::tuple_cat_t<
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        AllClientboundConfigurationMessages,
#endif
        AllClientboundLoginMessages,
        AllClientboundStatusMessages,
        AllClientboundPlayMessages
    >;
} //ProtocolCraft
