#pragma once

#include "protocolCraft/Utilities/Templates.hpp"

// Configuration
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundCookieRequestPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundCustomPayloadPacket.hpp"
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundCustomReportDetailsPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundDisconnectPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundFinishConfigurationPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundKeepAlivePacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundPingPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundRegistryDataPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundResetChatPacket.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPopConfigurationPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPushConfigurationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */ && PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundSelectKnownPacksPacket.hpp"
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundServerLinksPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundStoreCookiePacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundTransferPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp"
#include "protocolCraft/Messages/Configuration/Clientbound/ClientboundUpdateTagsPacket.hpp"
#endif

// Login
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Login/Clientbound/ClientboundCookieRequestPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Login/Clientbound/ClientboundCustomQueryPacket.hpp"
#endif
#include "protocolCraft/Messages/Login/Clientbound/ClientboundGameProfilePacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundHelloPacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundLoginCompressionPacket.hpp"
#include "protocolCraft/Messages/Login/Clientbound/ClientboundLoginDisconnectPacket.hpp"

// Play
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddExperienceOrbPacket.hpp"
#if PROTOCOL_VERSION < 735 /* < 1.16 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddGlobalEntityPacket.hpp"
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddMobPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddPaintingPacket.hpp"
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddPlayerPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAddVibrationSignalPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAnimatePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundAwardStatsPacket.hpp"
#if PROTOCOL_VERSION > 490 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockBreakAckPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockChangedAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockDestructionPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockEntityDataPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBlockUpdatePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBossEventPacket.hpp"
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundBundlePacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChangeDifficultyPacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChunkBatchFinishedPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChunkBatchStartPacket.hpp"
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChunksBiomesPacket.hpp"
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChatPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundChatPreviewPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundClearTitlesPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCommandSuggestionsPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCommandsPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerClosePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetContentPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetDataPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetSlotPacket.hpp"
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCookieRequestPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCooldownPacket.hpp"
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomChatCompletionsPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomPayloadPacket.hpp"
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomReportDetailsPacket.hpp"
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomSoundPacket.hpp"
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDamageEventPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDebugSamplePacket.hpp"
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDeleteChatPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDisconnectPacket.hpp"
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundDisguisedChatPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundEntityEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundExplodePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundForgetLevelChunkPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundGameEventPacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundHorseScreenOpenPacket.hpp"
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundHurtAnimationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundInitializeBorderPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundKeepAlivePacket.hpp"
#if PROTOCOL_VERSION < 757 /* < 1.18 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkPacket.hpp"
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkWithLightPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelEventPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLevelParticlesPacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLightUpdatePacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundLoginPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMapItemDataPacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMerchantOffersPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketPos.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketPosRot.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketRot.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundMoveVehiclePacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundOpenBookPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundOpenScreenPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundOpenSignEditorPacket.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPingPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlaceGhostRecipePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerAbilitiesPacket.hpp"
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerChatHeaderPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerChatPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatEndPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatEnterPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatKillPacket.hpp"
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoPacket.hpp"
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoRemovePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoUpdatePacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerLookAtPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPlayerPositionPacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundPongResponsePacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundProjectilePowerPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRecipePacket.hpp"
#if PROTOCOL_VERSION < 755 /* < 1.17 */ || PROTOCOL_VERSION > 755 /* > 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntitiesPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 756 /* < 1.17.1 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntityPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRemoveMobEffectPacket.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResetScorePacket.hpp"
#endif
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPacket.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPopPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPushPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRespawnPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundRotateHeadPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSelectAdvancementsTabPacket.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundServerDataPacket.hpp"
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundServerLinksPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetActionBarTextPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderCenterPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderLerpSizePacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderSizePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderWarningDelayPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderWarningDistancePacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetCameraPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetCarriedItemPacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheCenterPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheRadiusPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetDefaultSpawnPositionPacket.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetDisplayChatPreviewPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetDisplayObjectivePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityDataPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityLinkPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityMotionPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetEquipmentPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetExperiencePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetHealthPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetObjectivePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetPassengersPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetPlayerTeamPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetScorePacket.hpp"
#if PROTOCOL_VERSION > 756 /* > 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetSimulationDistancePacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetSubtitleTextPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTimePacket.hpp"
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTitlesPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTitleTextPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSetTitlesAnimationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSoundEntityPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSoundPacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundStartConfigurationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundStopSoundPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundStoreCookiePacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundSystemChatPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTabListPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTagQueryPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTakeItemEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTeleportEntityPacket.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTickingStatePacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTickingStepPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundTransferPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAdvancementsPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAttributesPacket.hpp"
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateMobEffectPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateRecipesPacket.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUpdateTagsPacket.hpp"
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
#include "protocolCraft/Messages/Play/Clientbound/ClientboundUseBedPacket.hpp"
#endif

// Status
#include "protocolCraft/Messages/Status/Clientbound/ClientboundPongResponsePacket.hpp"
#include "protocolCraft/Messages/Status/Clientbound/ClientboundStatusResponsePacket.hpp"


namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    using AllClientboundConfigurationMessages = std::tuple<
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundCookieRequestConfigurationPacket,
#endif
        ClientboundCustomPayloadConfigurationPacket,
        ClientboundDisconnectConfigurationPacket,
        ClientboundFinishConfigurationPacket,
        ClientboundKeepAliveConfigurationPacket,
        ClientboundPingConfigurationPacket,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundResetChatPacket,
#endif
        ClientboundRegistryDataPacket,
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        ClientboundResourcePackPopConfigurationPacket,
        ClientboundResourcePackPushConfigurationPacket,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundStoreCookieConfigurationPacket,
        ClientboundTransferConfigurationPacket,
#endif
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        ClientboundResourcePackConfigurationPacket,
#endif
        ClientboundUpdateEnabledFeaturesPacket,
        ClientboundUpdateTagsConfigurationPacket
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ,
        ClientboundSelectKnownPacksPacket
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        ,
        ClientboundCustomReportDetailsConfigurationPacket,
        ClientboundServerLinksConfigurationPacket
#endif
    >;
#endif

    using AllClientboundLoginMessages = std::tuple<
        ClientboundLoginDisconnectPacket,
        ClientboundHelloPacket,
        ClientboundGameProfilePacket,
        ClientboundLoginCompressionPacket
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ,
        ClientboundCustomQueryPacket
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ,
        ClientboundCookieRequestLoginPacket
#endif
    >;

    using AllClientboundPlayMessages = std::tuple<
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ClientboundBundlePacket,
#endif
        ClientboundAddEntityPacket,
        ClientboundAddExperienceOrbPacket,
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        ClientboundAddGlobalEntityPacket,
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        ClientboundAddMobPacket,
        ClientboundAddPaintingPacket,
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        ClientboundAddPlayerPacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        ClientboundAddVibrationSignalPacket,
#endif
        ClientboundAnimatePacket,
        ClientboundAwardStatsPacket,
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        ClientboundBlockChangedAckPacket,
#endif
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        ClientboundBlockBreakAckPacket,
#endif
        ClientboundBlockDestructionPacket,
        ClientboundBlockEntityDataPacket,
        ClientboundBlockEventPacket,
        ClientboundBlockUpdatePacket,
        ClientboundBossEventPacket,
        ClientboundChangeDifficultyPacket,
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ClientboundChunkBatchFinishedPacket,
        ClientboundChunkBatchStartPacket,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ClientboundChunksBiomesPacket,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundChatPreviewPacket,
#endif
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        ClientboundCommandSuggestionsPacket,
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        ClientboundChatPacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ClientboundClearTitlesPacket,
#endif
#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
        ClientboundSectionBlocksUpdatePacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ClientboundCommandSuggestionsPacket,
        ClientboundCommandsPacket,
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundContainerAckPacket,
#endif
        ClientboundContainerClosePacket,
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        ClientboundOpenScreenPacket,
#endif
        ClientboundContainerSetContentPacket,
        ClientboundContainerSetDataPacket,
        ClientboundContainerSetSlotPacket,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundCookieRequestPacket,
#endif
        ClientboundCooldownPacket,
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        ClientboundCustomChatCompletionsPacket,
#endif
        ClientboundCustomPayloadPacket,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ClientboundDamageEventPacket,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundDebugSamplePacket,
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundCustomSoundPacket,
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        ClientboundDeleteChatPacket,
#endif
        ClientboundDisconnectPacket,
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        ClientboundDisguisedChatPacket,
#endif
        ClientboundEntityEventPacket,
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 477 /* < 1.14 */
        ClientboundTagQueryPacket,
#endif
        ClientboundExplodePacket,
        ClientboundForgetLevelChunkPacket,
        ClientboundGameEventPacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundHorseScreenOpenPacket,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ClientboundHurtAnimationPacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ClientboundInitializeBorderPacket,
#endif
        ClientboundKeepAlivePacket,
#if PROTOCOL_VERSION < 757 /* < 1.18 */
        ClientboundLevelChunkPacket,
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        ClientboundLevelChunkWithLightPacket,
#endif
        ClientboundLevelEventPacket,
        ClientboundLevelParticlesPacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundLightUpdatePacket,
#endif
        ClientboundLoginPacket,
        ClientboundMapItemDataPacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundMerchantOffersPacket,
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        ClientboundMoveEntityPacket,
#endif
        ClientboundMoveEntityPacketPos,
        ClientboundMoveEntityPacketPosRot,
        ClientboundMoveEntityPacketRot,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundMoveEntityPacket,
#endif
        ClientboundMoveVehiclePacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundOpenBookPacket,
        ClientboundOpenScreenPacket,
#endif
        ClientboundOpenSignEditorPacket,
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ClientboundPingPacket,
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ClientboundPongResponsePacket,
#endif
        ClientboundPlaceGhostRecipePacket,
        ClientboundPlayerAbilitiesPacket,
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundPlayerChatHeaderPacket,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        ClientboundPlayerChatPacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ClientboundPlayerCombatEndPacket,
        ClientboundPlayerCombatEnterPacket,
        ClientboundPlayerCombatKillPacket,
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        ClientboundPlayerInfoRemovePacket,
        ClientboundPlayerInfoUpdatePacket,
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundPlayerCombatPacket,
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundPlayerInfoPacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ClientboundPlayerLookAtPacket,
#endif
        ClientboundPlayerPositionPacket,
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        ClientboundUseBedPacket,
#endif
        ClientboundRecipePacket,
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 756 /* < 1.17.1 */
        ClientboundRemoveEntityPacket,
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */ || PROTOCOL_VERSION > 755 /* > 1.17 */
        ClientboundRemoveEntitiesPacket,
#endif
        ClientboundRemoveMobEffectPacket,
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        ClientboundResetScorePacket,
        ClientboundResourcePackPopPacket,
        ClientboundResourcePackPushPacket,
#endif
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        ClientboundResourcePackPacket,
#endif
        ClientboundRespawnPacket,
        ClientboundRotateHeadPacket,
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        ClientboundSectionBlocksUpdatePacket,
#endif
        ClientboundSelectAdvancementsTabPacket,
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        ClientboundServerDataPacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ClientboundSetActionBarTextPacket,
        ClientboundSetBorderCenterPacket,
        ClientboundSetBorderLerpSizePacket,
        ClientboundSetBorderSizePacket,
        ClientboundSetBorderWarningDelayPacket,
        ClientboundSetBorderWarningDistancePacket,
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundSetBorderPacket,
#endif
        ClientboundSetCameraPacket,
        ClientboundSetCarriedItemPacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundSetChunkCacheCenterPacket,
        ClientboundSetChunkCacheRadiusPacket,
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        ClientboundSetDefaultSpawnPositionPacket,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ClientboundSetDisplayChatPreviewPacket,
#endif
        ClientboundSetDisplayObjectivePacket,
        ClientboundSetEntityDataPacket,
        ClientboundSetEntityLinkPacket,
        ClientboundSetEntityMotionPacket,
        ClientboundSetEquipmentPacket,
        ClientboundSetExperiencePacket,
        ClientboundSetHealthPacket,
        ClientboundSetObjectivePacket,
        ClientboundSetPassengersPacket,
        ClientboundSetPlayerTeamPacket,
        ClientboundSetScorePacket,
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        ClientboundSetSimulationDistancePacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ClientboundSetSubtitleTextPacket,
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        ClientboundSetDefaultSpawnPositionPacket,
#endif
        ClientboundSetTimePacket,
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ClientboundSetTitleTextPacket,
        ClientboundSetTitlesAnimationPacket,
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ClientboundSetTitlesPacket,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundSoundEntityPacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 477 /* < 1.14 */
        ClientboundStopSoundPacket,
#endif
        ClientboundSoundPacket,
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ClientboundStartConfigurationPacket,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundStopSoundPacket,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundStoreCookiePacket,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        ClientboundSystemChatPacket,
#endif
        ClientboundTabListPacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundTagQueryPacket,
#endif
        ClientboundTakeItemEntityPacket,
        ClientboundTeleportEntityPacket,
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        ClientboundTickingStatePacket,
        ClientboundTickingStepPacket,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ClientboundTransferPacket,
#endif
        ClientboundUpdateAdvancementsPacket,
        ClientboundUpdateAttributesPacket,
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        ClientboundUpdateEnabledFeaturesPacket,
#endif
        ClientboundUpdateMobEffectPacket
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ,
        ClientboundUpdateRecipesPacket,
        ClientboundUpdateTagsPacket
#endif
#if PROTOCOL_VERSION > 490 /* > 1.14.3 */ && PROTOCOL_VERSION < 573 /* < 1.15 */
        ,
        ClientboundBlockBreakAckPacket
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ,
        ClientboundProjectilePowerPacket
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        ,
        ClientboundCustomReportDetailsPacket,
        ClientboundServerLinksPacket
#endif
    >;

    using AllClientboundStatusMessages = std::tuple<
        ClientboundStatusResponsePacket,
        ClientboundPongResponseStatusPacket
    >;

    using AllClientboundMessages = Internal::tuple_cat_t<
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        AllClientboundConfigurationMessages,
#endif
        AllClientboundLoginMessages,
        AllClientboundPlayMessages,
        AllClientboundStatusMessages
    >;
} //ProtocolCraft
