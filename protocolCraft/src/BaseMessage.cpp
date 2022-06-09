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
#if PROTOCOL_VERSION > 340
    template class BaseMessage<ServerboundCustomQueryPacket>;
#endif
    template class BaseMessage<ServerboundHelloPacket>;
    template class BaseMessage<ServerboundKeyPacket>;

    // Login clientbound
#if PROTOCOL_VERSION > 340
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
#if PROTOCOL_VERSION > 476
    template class BaseMessage<ServerboundContainerButtonClickPacket>;
#endif
    template class BaseMessage<ServerboundClientInformationPacket>;
    template class BaseMessage<ServerboundClientCommandPacket>;
    template class BaseMessage<ServerboundContainerClosePacket>;
#if PROTOCOL_VERSION < 755
    template class BaseMessage<ServerboundContainerAckPacket>;
#endif
    template class BaseMessage<ServerboundPlaceRecipePacket>;
    template class BaseMessage<ServerboundSetCreativeModeSlotPacket>;
#if PROTOCOL_VERSION > 385
    template class BaseMessage<ServerboundEditBookPacket>;
#endif
#if PROTOCOL_VERSION < 476
    template class BaseMessage<ServerboundEnchantItemPacket>;
#endif
    template class BaseMessage<ServerboundPlayerCommandPacket>;
#if PROTOCOL_VERSION > 711
    template class BaseMessage<ServerboundJigsawGeneratePacket>;
#endif
    template class BaseMessage<ServerboundSetCarriedItemPacket>;
    template class BaseMessage<ServerboundInteractPacket>;
    template class BaseMessage<ServerboundKeepAlivePacket>;
#if PROTOCOL_VERSION > 463
    template class BaseMessage<ServerboundLockDifficultyPacket>;
#endif
#if PROTOCOL_VERSION > 385
    template class BaseMessage<ServerboundRenameItemPacket>;
    template class BaseMessage<ServerboundPickItemPacket>;
#endif
    template class BaseMessage<ServerboundPlayerAbilitiesPacket>;
    template class BaseMessage<ServerboundUseItemOnPacket>;
    template class BaseMessage<ServerboundPlayerActionPacket>;
    template class BaseMessage<ServerboundMovePlayerPacketRot>;
#if PROTOCOL_VERSION > 754
    template class BaseMessage<ServerboundMovePlayerPacketStatusOnly>;
#endif
#if PROTOCOL_VERSION < 755
    template class BaseMessage<ServerboundMovePlayerPacket>;
#endif
    template class BaseMessage<ServerboundMovePlayerPacketPos>;
    template class BaseMessage<ServerboundMovePlayerPacketPosRot>;
    template class BaseMessage<ServerboundCustomPayloadPacket>;
#if PROTOCOL_VERSION > 388
    template class BaseMessage<ServerboundBlockEntityTagQuery>;
    template class BaseMessage<ServerboundEntityTagQuery>;
#endif
#if PROTOCOL_VERSION < 736
    template class BaseMessage<ServerboundRecipeBookUpdatePacket>;
#else
    template class BaseMessage<ServerboundRecipeBookSeenRecipePacket>;
    template class BaseMessage<ServerboundRecipeBookChangeSettingsPacket>;
#endif
    template class BaseMessage<ServerboundResourcePackPacket>;
#if PROTOCOL_VERSION > 385
    template class BaseMessage<ServerboundSelectTradePacket>;
    template class BaseMessage<ServerboundSetBeaconPacket>;
#endif
#if PROTOCOL_VERSION > 463
    template class BaseMessage<ServerboundChangeDifficultyPacket>;
#endif
    template class BaseMessage<ServerboundTeleportToEntityPacket>;
    template class BaseMessage<ServerboundPaddleBoatPacket>;
    template class BaseMessage<ServerboundPlayerInputPacket>;
#if PROTOCOL_VERSION > 754
    template class BaseMessage<ServerboundPongPacket>;
#endif
    template class BaseMessage<ServerboundCommandSuggestionPacket>;
    template class BaseMessage<ServerboundAcceptTeleportationPacket>;
#if PROTOCOL_VERSION > 385
    template class BaseMessage<ServerboundSetCommandBlockPacket>;
    template class BaseMessage<ServerboundSetCommandMinecartPacket>;
#endif
#if PROTOCOL_VERSION > 471
    template class BaseMessage<ServerboundSetJigsawBlockPacket>;
#endif
    template class BaseMessage<ServerboundSignUpdatePacket>;
#if PROTOCOL_VERSION > 385
    template class BaseMessage<ServerboundSetStructureBlockPacket>;
#endif
    template class BaseMessage<ServerboundUseItemPacket>;
    template class BaseMessage<ServerboundMoveVehiclePacket>;

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
#if PROTOCOL_VERSION < 755
    template class BaseMessage<ClientboundPlayerCombatPacket>;
#endif
#if PROTOCOL_VERSION == 755
    template class BaseMessage<ClientboundRemoveEntityPacket>;
#else
    template class BaseMessage<ClientboundRemoveEntitiesPacket>;
#endif
#if PROTOCOL_VERSION > 345
    template class BaseMessage<ClientboundCommandsPacket>;
#endif
#if PROTOCOL_VERSION > 347
    template class BaseMessage<ClientboundUpdateRecipesPacket>;
#endif
#if PROTOCOL_VERSION > 351
    template class BaseMessage<ClientboundPlayerLookAtPacket>;
#endif
    template class BaseMessage<ClientboundChangeDifficultyPacket>;
    template class BaseMessage<ClientboundMapItemDataPacket>;
    template class BaseMessage<ClientboundSectionBlocksUpdatePacket>;
#if PROTOCOL_VERSION < 755
    template class BaseMessage<ClientboundContainerAckPacket>;
#endif
    template class BaseMessage<ClientboundGameEventPacket>;
    template class BaseMessage<ClientboundPlaceGhostRecipePacket>;
    template class BaseMessage<ClientboundDisconnectPacket>;
    template class BaseMessage<ClientboundSetDisplayObjectivePacket>;
    template class BaseMessage<ClientboundForgetLevelChunkPacket>;
    template class BaseMessage<ClientboundKeepAlivePacket>;
    template class BaseMessage<ClientboundCustomSoundPacket>;
#if PROTOCOL_VERSION > 388
    template class BaseMessage<ClientboundTagQueryPacket>;
#endif
    template class BaseMessage<ClientboundOpenSignEditorPacket>;
#if PROTOCOL_VERSION > 451
    template class BaseMessage<ClientboundHorseScreenOpenPacket>;
#endif
#if PROTOCOL_VERSION > 450
    template class BaseMessage<ClientboundOpenBookPacket>;
#endif
#if PROTOCOL_VERSION < 757
    template class BaseMessage<ClientboundLevelChunkPacket>;
#endif
    template class BaseMessage<ClientboundLoginPacket>;
    template class BaseMessage<ClientboundLevelEventPacket>;
#if PROTOCOL_VERSION < 755
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
#if PROTOCOL_VERSION > 450
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
    template class BaseMessage<ClientboundChatPacket>;
    template class BaseMessage<ClientboundRespawnPacket>;
#if PROTOCOL_VERSION > 404
    template class BaseMessage<ClientboundLightUpdatePacket>;
#endif
#if PROTOCOL_VERSION > 493
    template class BaseMessage<ClientboundBlockBreakAckPacket>;
#endif
    template class BaseMessage<ClientboundBlockEntityDataPacket>;
    template class BaseMessage<ClientboundPlayerInfoPacket>;
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
#if PROTOCOL_VERSION < 721
    template class BaseMessage<ClientboundAddGlobalEntityPacket>;
#endif
    template class BaseMessage<ClientboundAddMobPacket>;
    template class BaseMessage<ClientboundAddEntityPacket>;
    template class BaseMessage<ClientboundAddPaintingPacket>;
    template class BaseMessage<ClientboundAddPlayerPacket>;
    template class BaseMessage<ClientboundSetDefaultSpawnPositionPacket>;
    template class BaseMessage<ClientboundAwardStatsPacket>;
#if PROTOCOL_VERSION > 342
    template class BaseMessage<ClientboundStopSoundPacket>;
#endif
#if PROTOCOL_VERSION > 348
    template class BaseMessage<ClientboundUpdateTagsPacket>;
#endif
    template class BaseMessage<ClientboundCommandSuggestionsPacket>;
    template class BaseMessage<ClientboundSetPlayerTeamPacket>;
#if PROTOCOL_VERSION < 755
    template class BaseMessage<ClientboundSetTitlesPacket>;
#endif
#if PROTOCOL_VERSION < 461
    template class BaseMessage<ClientboundUseBedPacket>;
#endif
#if PROTOCOL_VERSION > 451
    template class BaseMessage<ClientboundMerchantOffersPacket>;
#endif
    template class BaseMessage<ClientboundRecipePacket>;
    template class BaseMessage<ClientboundSetScorePacket>;
#if PROTOCOL_VERSION > 471
    template class BaseMessage<ClientboundSetChunkCacheCenterPacket>;
    template class BaseMessage<ClientboundSetChunkCacheRadiusPacket>;
#endif
    template class BaseMessage<ClientboundMoveVehiclePacket>;
    template class BaseMessage<ClientboundContainerSetContentPacket>;
    template class BaseMessage<ClientboundContainerSetDataPacket>;
    template class BaseMessage<ClientboundOpenScreenPacket>;
    template class BaseMessage<ClientboundSetCarriedItemPacket>;
#if PROTOCOL_VERSION < 755
    template class BaseMessage<ClientboundSetBorderPacket>;
#endif
#if PROTOCOL_VERSION > 754
    template class BaseMessage<ClientboundAddVibrationSignalPacket>;
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
#if PROTOCOL_VERSION > 756
    template class BaseMessage<ClientboundLevelChunkWithLightPacket>;
    template class BaseMessage<ClientboundSetSimulationDistancePacket>;
#endif
}