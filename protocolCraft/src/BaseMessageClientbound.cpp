#include "protocolCraft/BaseMessage.ipp"
#include "protocolCraft/AllClientboundMessages.hpp"

namespace ProtocolCraft
{
    // Explicit instantiation for each clientbound message class

    // Login clientbound
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    template class BaseMessage<ClientboundCookieRequestLoginPacket>;
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    template class BaseMessage<ClientboundCustomQueryPacket>;
#endif
    template class BaseMessage<ClientboundLoginDisconnectPacket>;
    template class BaseMessage<ClientboundHelloPacket>;
    template class BaseMessage<ClientboundGameProfilePacket>;
    template class BaseMessage<ClientboundLoginCompressionPacket>;

    // Status clientbound
    template class BaseMessage<ClientboundStatusResponsePacket>;
    template class BaseMessage<ClientboundPongResponseStatusPacket>;

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    // Configuration clientbound
    template class BaseMessage<ClientboundCustomPayloadConfigurationPacket>;
    template class BaseMessage<ClientboundDisconnectConfigurationPacket>;
    template class BaseMessage<ClientboundFinishConfigurationPacket>;
    template class BaseMessage<ClientboundKeepAliveConfigurationPacket>;
    template class BaseMessage<ClientboundPingConfigurationPacket>;
    template class BaseMessage<ClientboundRegistryDataPacket>;
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    template class BaseMessage<ClientboundResourcePackConfigurationPacket>;
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    template class BaseMessage<ClientboundResourcePackPopConfigurationPacket>;
    template class BaseMessage<ClientboundResourcePackPushConfigurationPacket>;
#endif
    template class BaseMessage<ClientboundUpdateEnabledFeaturesPacket>;
    template class BaseMessage<ClientboundUpdateTagsConfigurationPacket>;
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    template class BaseMessage<ClientboundCookieRequestConfigurationPacket>;
    template class BaseMessage<ClientboundResetChatPacket>;
    template class BaseMessage<ClientboundStoreCookieConfigurationPacket>;
    template class BaseMessage<ClientboundSelectKnownPacksPacket>;
    template class BaseMessage<ClientboundTransferConfigurationPacket>;
#endif
#endif

    // Play clientbound
    template class BaseMessage<ClientboundUpdateAdvancementsPacket>;
    template class BaseMessage<ClientboundSetEntityLinkPacket>;
    template class BaseMessage<ClientboundBlockEventPacket>;
    template class BaseMessage<ClientboundBlockDestructionPacket>;
    template class BaseMessage<ClientboundBlockUpdatePacket>;
    template class BaseMessage<ClientboundBossEventPacket>;
    template class BaseMessage<ClientboundSetCameraPacket>;
    template class BaseMessage<ClientboundContainerClosePacket>;
    template class BaseMessage<ClientboundTakeItemEntityPacket>;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    template class BaseMessage<ClientboundPlayerCombatPacket>;
#endif
#if PROTOCOL_VERSION == 755 /* 1.17 */
    template class BaseMessage<ClientboundRemoveEntityPacket>;
#else
    template class BaseMessage<ClientboundRemoveEntitiesPacket>;
#endif
#if PROTOCOL_VERSION > 345 /* > 1.12.2 */
    template class BaseMessage<ClientboundCommandsPacket>;
#endif
#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
    template class BaseMessage<ClientboundUpdateRecipesPacket>;
#endif
#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
    template class BaseMessage<ClientboundPlayerLookAtPacket>;
#endif
    template class BaseMessage<ClientboundChangeDifficultyPacket>;
    template class BaseMessage<ClientboundMapItemDataPacket>;
    template class BaseMessage<ClientboundSectionBlocksUpdatePacket>;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    template class BaseMessage<ClientboundContainerAckPacket>;
#endif
    template class BaseMessage<ClientboundGameEventPacket>;
    template class BaseMessage<ClientboundPlaceGhostRecipePacket>;
    template class BaseMessage<ClientboundDisconnectPacket>;
    template class BaseMessage<ClientboundSetDisplayObjectivePacket>;
    template class BaseMessage<ClientboundForgetLevelChunkPacket>;
    template class BaseMessage<ClientboundKeepAlivePacket>;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    template class BaseMessage<ClientboundCustomSoundPacket>;
#endif
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
    template class BaseMessage<ClientboundTagQueryPacket>;
#endif
    template class BaseMessage<ClientboundOpenSignEditorPacket>;
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
    template class BaseMessage<ClientboundHorseScreenOpenPacket>;
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
    template class BaseMessage<ClientboundOpenBookPacket>;
#endif
#if PROTOCOL_VERSION < 757 /* < 1.18 */
    template class BaseMessage<ClientboundLevelChunkPacket>;
#endif
    template class BaseMessage<ClientboundLoginPacket>;
    template class BaseMessage<ClientboundLevelEventPacket>;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    template class BaseMessage<ClientboundMoveEntityPacket>;
#endif
    template class BaseMessage<ClientboundAnimatePacket>;
    template class BaseMessage<ClientboundSetEquipmentPacket>;
    template class BaseMessage<ClientboundUpdateMobEffectPacket>;
    template class BaseMessage<ClientboundRotateHeadPacket>;
    template class BaseMessage<ClientboundMoveEntityPacketPos>;
    template class BaseMessage<ClientboundMoveEntityPacketPosRot>;
    template class BaseMessage<ClientboundMoveEntityPacketRot>;
    template class BaseMessage<ClientboundSetEntityDataPacket>;
    template class BaseMessage<ClientboundUpdateAttributesPacket>;
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
    template class BaseMessage<ClientboundSoundEntityPacket>;
#endif
    template class BaseMessage<ClientboundEntityEventPacket>;
    template class BaseMessage<ClientboundSetEntityMotionPacket>;
    template class BaseMessage<ClientboundExplodePacket>;
    template class BaseMessage<ClientboundLevelParticlesPacket>;
    template class BaseMessage<ClientboundPlayerPositionPacket>;
    template class BaseMessage<ClientboundSetHealthPacket>;
    template class BaseMessage<ClientboundTeleportEntityPacket>;
    template class BaseMessage<ClientboundPlayerAbilitiesPacket>;
    template class BaseMessage<ClientboundSetTimePacket>;
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    template class BaseMessage<ClientboundChatPacket>;
#endif
    template class BaseMessage<ClientboundRespawnPacket>;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    template class BaseMessage<ClientboundLightUpdatePacket>;
#endif
#if PROTOCOL_VERSION > 493 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
    template class BaseMessage<ClientboundBlockBreakAckPacket>;
#endif
    template class BaseMessage<ClientboundBlockEntityDataPacket>;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    template class BaseMessage<ClientboundPlayerInfoPacket>;
#endif
    template class BaseMessage<ClientboundTabListPacket>;
    template class BaseMessage<ClientboundCustomPayloadPacket>;
    template class BaseMessage<ClientboundRemoveMobEffectPacket>;
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    template class BaseMessage<ClientboundResourcePackPacket>;
#endif
    template class BaseMessage<ClientboundSetObjectivePacket>;
    template class BaseMessage<ClientboundSelectAdvancementsTabPacket>;
    template class BaseMessage<ClientboundSetExperiencePacket>;
    template class BaseMessage<ClientboundContainerSetSlotPacket>;
    template class BaseMessage<ClientboundCooldownPacket>;
    template class BaseMessage<ClientboundSetPassengersPacket>;
    template class BaseMessage<ClientboundSoundPacket>;
    template class BaseMessage<ClientboundAddExperienceOrbPacket>;
#if PROTOCOL_VERSION < 721 /* < 1.16 */
    template class BaseMessage<ClientboundAddGlobalEntityPacket>;
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    template class BaseMessage<ClientboundAddMobPacket>;
#endif
    template class BaseMessage<ClientboundAddEntityPacket>;
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    template class BaseMessage<ClientboundAddPaintingPacket>;
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    template class BaseMessage<ClientboundAddPlayerPacket>;
#endif
    template class BaseMessage<ClientboundSetDefaultSpawnPositionPacket>;
    template class BaseMessage<ClientboundAwardStatsPacket>;
#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
    template class BaseMessage<ClientboundStopSoundPacket>;
#endif
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
    template class BaseMessage<ClientboundUpdateTagsPacket>;
#endif
    template class BaseMessage<ClientboundCommandSuggestionsPacket>;
    template class BaseMessage<ClientboundSetPlayerTeamPacket>;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    template class BaseMessage<ClientboundSetTitlesPacket>;
#endif
#if PROTOCOL_VERSION < 461 /* < 1.14 */
    template class BaseMessage<ClientboundUseBedPacket>;
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
    template class BaseMessage<ClientboundMerchantOffersPacket>;
#endif
    template class BaseMessage<ClientboundRecipePacket>;
    template class BaseMessage<ClientboundSetScorePacket>;
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
    template class BaseMessage<ClientboundSetChunkCacheCenterPacket>;
    template class BaseMessage<ClientboundSetChunkCacheRadiusPacket>;
#endif
    template class BaseMessage<ClientboundMoveVehiclePacket>;
    template class BaseMessage<ClientboundContainerSetContentPacket>;
    template class BaseMessage<ClientboundContainerSetDataPacket>;
    template class BaseMessage<ClientboundOpenScreenPacket>;
    template class BaseMessage<ClientboundSetCarriedItemPacket>;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    template class BaseMessage<ClientboundSetBorderPacket>;
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    template class BaseMessage<ClientboundAddVibrationSignalPacket>;
#endif
    template class BaseMessage<ClientboundClearTitlesPacket>;
    template class BaseMessage<ClientboundInitializeBorderPacket>;
    template class BaseMessage<ClientboundPingPacket>;
    template class BaseMessage<ClientboundPlayerCombatEndPacket>;
    template class BaseMessage<ClientboundPlayerCombatEnterPacket>;
    template class BaseMessage<ClientboundPlayerCombatKillPacket>;
    template class BaseMessage<ClientboundSetActionBarTextPacket>;
    template class BaseMessage<ClientboundSetBorderCenterPacket>;
    template class BaseMessage<ClientboundSetBorderLerpSizePacket>;
    template class BaseMessage<ClientboundSetBorderSizePacket>;
    template class BaseMessage<ClientboundSetBorderWarningDelayPacket>;
    template class BaseMessage<ClientboundSetBorderWarningDistancePacket>;
    template class BaseMessage<ClientboundSetSubtitleTextPacket>;
    template class BaseMessage<ClientboundSetTitleTextPacket>;
    template class BaseMessage<ClientboundSetTitlesAnimationPacket>;
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    template class BaseMessage<ClientboundLevelChunkWithLightPacket>;
    template class BaseMessage<ClientboundSetSimulationDistancePacket>;
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    template class BaseMessage<ClientboundBlockChangedAckPacket>;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    template class BaseMessage<ClientboundChatPreviewPacket>;
#endif
    template class BaseMessage<ClientboundPlayerChatPacket>;
    template class BaseMessage<ClientboundServerDataPacket>;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    template class BaseMessage<ClientboundSetDisplayChatPreviewPacket>;
#endif
    template class BaseMessage<ClientboundSystemChatPacket>;
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    template class BaseMessage<ClientboundCustomChatCompletionsPacket>;
    template class BaseMessage<ClientboundDeleteChatPacket>;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    template class BaseMessage<ClientboundPlayerChatHeaderPacket>;
#endif
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    template class BaseMessage<ClientboundDisguisedChatPacket>;
    template class BaseMessage<ClientboundPlayerInfoRemovePacket>;
    template class BaseMessage<ClientboundPlayerInfoUpdatePacket>;
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    template class BaseMessage<ClientboundUpdateEnabledFeaturesPacket>;
#endif
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
    template class BaseMessage<ClientboundBundlePacket>;
    template class BaseMessage<ClientboundChunksBiomesPacket>;
    template class BaseMessage<ClientboundDamageEventPacket>;
    template class BaseMessage<ClientboundHurtAnimationPacket>;
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    template class BaseMessage<ClientboundChunkBatchFinishedPacket>;
    template class BaseMessage<ClientboundChunkBatchStartPacket>;
    template class BaseMessage<ClientboundPongResponsePacket>;
    template class BaseMessage<ClientboundStartConfigurationPacket>;
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    template class BaseMessage<ClientboundResetScorePacket>;
    template class BaseMessage<ClientboundResourcePackPopPacket>;
    template class BaseMessage<ClientboundResourcePackPushPacket>;
    template class BaseMessage<ClientboundTickingStatePacket>;
    template class BaseMessage<ClientboundTickingStepPacket>;
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    template class BaseMessage<ClientboundCookieRequestPacket>;
    template class BaseMessage<ClientboundDebugSamplePacket>;
    template class BaseMessage<ClientboundProjectilePowerPacket>;
    template class BaseMessage<ClientboundStoreCookiePacket>;
    template class BaseMessage<ClientboundTransferPacket>;
#endif
}
