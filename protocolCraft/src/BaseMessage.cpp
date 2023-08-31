#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/AllMessages.hpp"
#include "protocolCraft/Handler.hpp"

namespace ProtocolCraft
{
    template <typename TDerived>
    void BaseMessage<TDerived>::DispatchImpl(Handler *handler)
    {
        handler->Handle(static_cast<TDerived&>(*this));
    }

    // Explicit instantiation for each message class
    // Handshaking serverbound
    template class BaseMessage<ServerboundClientIntentionPacket>;


    // Login serverbound
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    template class BaseMessage<ServerboundCustomQueryPacket>;
#endif
    template class BaseMessage<ServerboundHelloPacket>;
    template class BaseMessage<ServerboundKeyPacket>;

    // Login clientbound
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    template class BaseMessage<ClientboundCustomQueryPacket>;
#endif
    template class BaseMessage<ClientboundLoginDisconnectPacket>;
    template class BaseMessage<ClientboundHelloPacket>;
    template class BaseMessage<ClientboundGameProfilePacket>;
    template class BaseMessage<ClientboundLoginCompressionPacket>;

    // Status serverbound
    template class BaseMessage<ServerboundStatusRequestPacket>;
    template class BaseMessage<ServerboundPingRequestPacket>;

    // Status clientbound
    template class BaseMessage<ClientboundStatusResponsePacket>;
    template class BaseMessage<ClientboundPongResponsePacket>;


    // Play serverbound
    template class BaseMessage<ServerboundSeenAdvancementsPacket>;
    template class BaseMessage<ServerboundSwingPacket>;
    template class BaseMessage<ServerboundChatPacket>;
    template class BaseMessage<ServerboundContainerClickPacket>;
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
    template class BaseMessage<ServerboundContainerButtonClickPacket>;
#endif
    template class BaseMessage<ServerboundClientInformationPacket>;
    template class BaseMessage<ServerboundClientCommandPacket>;
    template class BaseMessage<ServerboundContainerClosePacket>;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    template class BaseMessage<ServerboundContainerAckPacket>;
#endif
    template class BaseMessage<ServerboundPlaceRecipePacket>;
    template class BaseMessage<ServerboundSetCreativeModeSlotPacket>;
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    template class BaseMessage<ServerboundEditBookPacket>;
#endif
#if PROTOCOL_VERSION < 476 /* < 1.14 */
    template class BaseMessage<ServerboundEnchantItemPacket>;
#endif
    template class BaseMessage<ServerboundPlayerCommandPacket>;
#if PROTOCOL_VERSION > 711 /* > 1.15.2 */
    template class BaseMessage<ServerboundJigsawGeneratePacket>;
#endif
    template class BaseMessage<ServerboundSetCarriedItemPacket>;
    template class BaseMessage<ServerboundInteractPacket>;
    template class BaseMessage<ServerboundKeepAlivePacket>;
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
    template class BaseMessage<ServerboundLockDifficultyPacket>;
#endif
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    template class BaseMessage<ServerboundRenameItemPacket>;
    template class BaseMessage<ServerboundPickItemPacket>;
#endif
    template class BaseMessage<ServerboundPlayerAbilitiesPacket>;
    template class BaseMessage<ServerboundUseItemOnPacket>;
    template class BaseMessage<ServerboundPlayerActionPacket>;
    template class BaseMessage<ServerboundMovePlayerPacketRot>;
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
    template class BaseMessage<ServerboundMovePlayerPacketStatusOnly>;
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    template class BaseMessage<ServerboundMovePlayerPacket>;
#endif
    template class BaseMessage<ServerboundMovePlayerPacketPos>;
    template class BaseMessage<ServerboundMovePlayerPacketPosRot>;
    template class BaseMessage<ServerboundCustomPayloadPacket>;
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
    template class BaseMessage<ServerboundBlockEntityTagQuery>;
    template class BaseMessage<ServerboundEntityTagQuery>;
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
    template class BaseMessage<ServerboundRecipeBookSeenRecipePacket>;
    template class BaseMessage<ServerboundRecipeBookChangeSettingsPacket>;
#else
    template class BaseMessage<ServerboundRecipeBookUpdatePacket>;
#endif
    template class BaseMessage<ServerboundResourcePackPacket>;
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    template class BaseMessage<ServerboundSelectTradePacket>;
    template class BaseMessage<ServerboundSetBeaconPacket>;
#endif
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
    template class BaseMessage<ServerboundChangeDifficultyPacket>;
#endif
    template class BaseMessage<ServerboundTeleportToEntityPacket>;
    template class BaseMessage<ServerboundPaddleBoatPacket>;
    template class BaseMessage<ServerboundPlayerInputPacket>;
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
    template class BaseMessage<ServerboundPongPacket>;
#endif
    template class BaseMessage<ServerboundCommandSuggestionPacket>;
    template class BaseMessage<ServerboundAcceptTeleportationPacket>;
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    template class BaseMessage<ServerboundSetCommandBlockPacket>;
    template class BaseMessage<ServerboundSetCommandMinecartPacket>;
#endif
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
    template class BaseMessage<ServerboundSetJigsawBlockPacket>;
#endif
    template class BaseMessage<ServerboundSignUpdatePacket>;
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    template class BaseMessage<ServerboundSetStructureBlockPacket>;
#endif
    template class BaseMessage<ServerboundUseItemPacket>;
    template class BaseMessage<ServerboundMoveVehiclePacket>;
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    template class BaseMessage<ServerboundChatCommandPacket>;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    template class BaseMessage<ServerboundChatPreviewPacket>;
#endif
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    template class BaseMessage<ServerboundChatAckPacket>;
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
    template class BaseMessage<ServerboundChatSessionUpdatePacket>;
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
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
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
    template class BaseMessage<ClientboundResourcePackPacket>;
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
    template class BaseMessage<ClientboundAddPlayerPacket>;
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
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
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
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
    template class BaseMessage<ClientboundDisguisedChatPacket>;
    template class BaseMessage<ClientboundPlayerInfoRemovePacket>;
    template class BaseMessage<ClientboundPlayerInfoUpdatePacket>;
    template class BaseMessage<ClientboundUpdateEnabledFeaturesPacket>;
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
    template class BaseMessage<ClientboundBundlePacket>;
    template class BaseMessage<ClientboundChunksBiomesPacket>;
    template class BaseMessage<ClientboundDamageEventPacket>;
    template class BaseMessage<ClientboundHurtAnimationPacket>;
#endif
}
