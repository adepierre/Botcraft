#pragma once

#include "protocolCraft/Utilities/Templates.hpp"

// Configuration
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundClearDialogPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundCookieRequestPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundCustomPayloadPacket.hpp"
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundCustomReportDetailsPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundDisconnectPacket.hpp"
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundFinishConfigurationPacket.hpp"
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundKeepAlivePacket.hpp"
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundPingPacket.hpp"
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundRegistryDataPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundResetChatPacket.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundResourcePackPopConfigurationPacket.hpp"
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundResourcePackPushConfigurationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */ && PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundResourcePackPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundSelectKnownPacksPacket.hpp"
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundServerLinksPacket.hpp"
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundShowDialogPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundStoreCookiePacket.hpp"
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundTransferPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp"
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundUpdateTagsPacket.hpp"
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Packets/Configuration/Clientbound/ClientboundCodeOfConductPacket.hpp"
#endif

// Login
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Login/Clientbound/ClientboundCookieRequestPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Login/Clientbound/ClientboundCustomQueryPacket.hpp"
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "protocolCraft/Packets/Login/Clientbound/ClientboundGameProfilePacket.hpp"
#endif
#include "protocolCraft/Packets/Login/Clientbound/ClientboundHelloPacket.hpp"
#include "protocolCraft/Packets/Login/Clientbound/ClientboundLoginCompressionPacket.hpp"
#include "protocolCraft/Packets/Login/Clientbound/ClientboundLoginDisconnectPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Login/Clientbound/ClientboundLoginFinishedPacket.hpp"
#endif

// Play
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAddEntityPacket.hpp"
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAddExperienceOrbPacket.hpp"
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAddGlobalEntityPacket.hpp"
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAddMobPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAddPaintingPacket.hpp"
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAddPlayerPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAddVibrationSignalPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAnimatePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundAwardStatsPacket.hpp"
#if PROTOCOL_VERSION > 490 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundBlockBreakAckPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundBlockChangedAckPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundBlockDestructionPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundBlockEntityDataPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundBlockEventPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundBlockUpdatePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundBossEventPacket.hpp"
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundBundlePacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundChangeDifficultyPacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundChunkBatchFinishedPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundChunkBatchStartPacket.hpp"
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundChunksBiomesPacket.hpp"
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundClearDialogPacket.hpp"
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundChatPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundChatPreviewPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundClearTitlesPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundCommandSuggestionsPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundCommandsPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundContainerAckPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundContainerClosePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundContainerSetContentPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundContainerSetDataPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundContainerSetSlotPacket.hpp"
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundCookieRequestPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundCooldownPacket.hpp"
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundCustomChatCompletionsPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundCustomPayloadPacket.hpp"
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundCustomReportDetailsPacket.hpp"
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundCustomSoundPacket.hpp"
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDamageEventPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDebugBlockValuePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDebugChunkValuePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDebugEntityValuePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDebugEventPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDebugSamplePacket.hpp"
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDeleteChatPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDisconnectPacket.hpp"
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundDisguisedChatPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundEntityEventPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundEntityPositionSyncPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundExplodePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundForgetLevelChunkPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundGameEventPacket.hpp"
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundGameTestHighlightPosPacket.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundHorseScreenOpenPacket.hpp"
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundHurtAnimationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundInitializeBorderPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundKeepAlivePacket.hpp"
#if PROTOCOL_VERSION < 757 /* < 1.18 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundLevelChunkPacket.hpp"
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundLevelChunkWithLightPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundLevelEventPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundLevelParticlesPacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundLightUpdatePacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundLoginPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundMapItemDataPacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundMerchantOffersPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundMoveEntityPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundMoveEntityPacketPos.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundMoveEntityPacketPosRot.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundMoveEntityPacketRot.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundMoveMinecartPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundMoveVehiclePacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundOpenBookPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundOpenScreenPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundOpenSignEditorPacket.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPingPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlaceGhostRecipePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerAbilitiesPacket.hpp"
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerChatHeaderPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerChatPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerCombatPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerCombatEndPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerCombatEnterPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerCombatKillPacket.hpp"
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerInfoPacket.hpp"
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerInfoRemovePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerInfoUpdatePacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerLookAtPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerPositionPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPlayerRotationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundPongResponsePacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundProjectilePowerPacket.hpp"
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRecipeBookAddPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRecipeBookRemovePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRecipeBookSettingsPacket.hpp"
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRecipePacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */ || PROTOCOL_VERSION > 755 /* > 1.17 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRemoveEntitiesPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 756 /* < 1.17.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRemoveEntityPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRemoveMobEffectPacket.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundResetScorePacket.hpp"
#endif
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundResourcePackPacket.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundResourcePackPopPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundResourcePackPushPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRespawnPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundRotateHeadPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSelectAdvancementsTabPacket.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundServerDataPacket.hpp"
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundServerLinksPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetActionBarTextPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderCenterPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderLerpSizePacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderSizePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderWarningDelayPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderWarningDistancePacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetCameraPacket.hpp"
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetCarriedItemPacket.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetChunkCacheCenterPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetChunkCacheRadiusPacket.hpp"
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetCursorItemPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetDefaultSpawnPositionPacket.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetDisplayChatPreviewPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetDisplayObjectivePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetEntityDataPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetEntityLinkPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetEntityMotionPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetEquipmentPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetExperiencePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetHealthPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetHeldSlotPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetObjectivePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetPassengersPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetPlayerInventoryPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetPlayerTeamPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetScorePacket.hpp"
#if PROTOCOL_VERSION > 756 /* > 1.17 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetSimulationDistancePacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetSubtitleTextPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetTimePacket.hpp"
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetTitlesPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetTitleTextPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSetTitlesAnimationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundShowDialogPacket.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSoundEntityPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSoundPacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundStartConfigurationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundStopSoundPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundStoreCookiePacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundSystemChatPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTabListPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTagQueryPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTakeItemEntityPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTeleportEntityPacket.hpp"
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTestInstanceBlockStatusPacket.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTickingStatePacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTickingStepPacket.hpp"
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTrackedWaypointPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundTransferPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundUpdateAdvancementsPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundUpdateAttributesPacket.hpp"
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Clientbound/ClientboundUpdateMobEffectPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundUpdateRecipesPacket.hpp"
#include "protocolCraft/Packets/Game/Clientbound/ClientboundUpdateTagsPacket.hpp"
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
#include "protocolCraft/Packets/Game/Clientbound/ClientboundUseBedPacket.hpp"
#endif

// Status
#include "protocolCraft/Packets/Status/Clientbound/ClientboundPongResponsePacket.hpp"
#include "protocolCraft/Packets/Status/Clientbound/ClientboundStatusResponsePacket.hpp"


namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    using AllClientboundConfigurationPackets = std::tuple<
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
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        ,
        ClientboundClearDialogConfigurationPacket,
        ClientboundShowDialogConfigurationPacket
#endif
    >;
#endif

    using AllClientboundLoginPackets = std::tuple<
        ClientboundLoginDisconnectPacket,
        ClientboundHelloPacket,
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        ClientboundGameProfilePacket,
#else
        ClientboundLoginFinishedPacket,
#endif
        ClientboundLoginCompressionPacket
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ,
        ClientboundCustomQueryPacket
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ,
        ClientboundCookieRequestLoginPacket
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        ,
        ClientboundCodeOfConductPacket
#endif
    >;

    using AllClientboundPlayPackets = std::tuple<
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ClientboundBundlePacket,
#endif
        ClientboundAddEntityPacket,
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        ClientboundAddExperienceOrbPacket,
#endif
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
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        ClientboundDebugBlockValuePacket,
        ClientboundDebugChunkValuePacket,
        ClientboundDebugEntityValuePacket,
        ClientboundDebugEventPacket,
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
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ClientboundEntityPositionSyncPacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 477 /* < 1.14 */
        ClientboundTagQueryPacket,
#endif
        ClientboundExplodePacket,
        ClientboundForgetLevelChunkPacket,
        ClientboundGameEventPacket,
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        ClientboundGameTestHighlightPosPacket,
#endif
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
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ClientboundMoveMinecartPacket,
#endif
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
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ClientboundPlayerRotationPacket,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ClientboundRecipeBookAddPacket,
        ClientboundRecipeBookRemovePacket,
        ClientboundRecipeBookSettingsPacket,
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        ClientboundUseBedPacket,
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        ClientboundRecipePacket,
#endif
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
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        ClientboundSetCarriedItemPacket,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ClientboundSetChunkCacheCenterPacket,
        ClientboundSetChunkCacheRadiusPacket,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ClientboundSetCursorItemPacket,
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
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ClientboundSetHeldSlotPacket,
#endif
        ClientboundSetObjectivePacket,
        ClientboundSetPassengersPacket,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ClientboundSetPlayerInventoryPacket,
#endif
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
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        ClientboundTestInstanceBlockStatusPacket,
#endif
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
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        ,
        ClientboundTrackedWaypointPacket,
        ClientboundClearDialogPacket,
        ClientboundShowDialogPacket
#endif
    >;

    using AllClientboundStatusPackets = std::tuple<
        ClientboundStatusResponsePacket,
        ClientboundPongResponseStatusPacket
    >;

    using AllClientboundPackets = Internal::tuple_cat_t<
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        AllClientboundConfigurationPackets,
#endif
        AllClientboundLoginPackets,
        AllClientboundPlayPackets,
        AllClientboundStatusPackets
    >;
} //ProtocolCraft
