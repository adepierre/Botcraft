project(protocolCraft)

set(protocolCraft_PUBLIC_HDR
    include/protocolCraft/AllClientboundPackets.hpp
    include/protocolCraft/AllPackets.hpp
    include/protocolCraft/AllServerboundPackets.hpp
    include/protocolCraft/BasePacket.hpp
    include/protocolCraft/BinaryReadWrite.hpp
    include/protocolCraft/enums.hpp
    include/protocolCraft/GenericHandler.hpp
    include/protocolCraft/Handler.hpp
    include/protocolCraft/NetworkType.hpp
    include/protocolCraft/Packet.hpp
    include/protocolCraft/PacketFactory.hpp

    include/protocolCraft/Packets/Handshake/Serverbound/ServerboundClientIntentionPacket.hpp


    include/protocolCraft/Packets/Login/Clientbound/ClientboundCookieRequestPacket.hpp
    include/protocolCraft/Packets/Login/Clientbound/ClientboundCustomQueryPacket.hpp
    include/protocolCraft/Packets/Login/Clientbound/ClientboundGameProfilePacket.hpp
    include/protocolCraft/Packets/Login/Clientbound/ClientboundHelloPacket.hpp
    include/protocolCraft/Packets/Login/Clientbound/ClientboundLoginCompressionPacket.hpp
    include/protocolCraft/Packets/Login/Clientbound/ClientboundLoginDisconnectPacket.hpp
    include/protocolCraft/Packets/Login/Clientbound/ClientboundLoginFinishedPacket.hpp

    include/protocolCraft/Packets/Login/Serverbound/ServerboundCookieResponsePacket.hpp
    include/protocolCraft/Packets/Login/Serverbound/ServerboundCustomQueryAnswerPacket.hpp
    include/protocolCraft/Packets/Login/Serverbound/ServerboundCustomQueryPacket.hpp
    include/protocolCraft/Packets/Login/Serverbound/ServerboundHelloPacket.hpp
    include/protocolCraft/Packets/Login/Serverbound/ServerboundKeyPacket.hpp
    include/protocolCraft/Packets/Login/Serverbound/ServerboundLoginAcknowledgedPacket.hpp


    include/protocolCraft/Packets/Game/Clientbound/ClientboundAddEntityPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundAddExperienceOrbPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundAddGlobalEntityPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundAddMobPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundAddPaintingPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundAddPlayerPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundAddVibrationSignalPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundAnimatePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundAwardStatsPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundBlockBreakAckPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundBlockChangedAckPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundBlockDestructionPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundBlockEntityDataPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundBlockEventPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundBlockUpdatePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundBossEventPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundBundlePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundChangeDifficultyPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundChatPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundChatPreviewPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundChunkBatchFinishedPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundChunkBatchStartPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundChunksBiomesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundClearDialogPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundClearTitlesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundCommandsPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundCommandSuggestionsPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundContainerAckPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundContainerClosePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundContainerSetContentPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundContainerSetDataPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundContainerSetSlotPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundCookieRequestPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundCooldownPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundCustomChatCompletionsPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundCustomPayloadPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundCustomReportDetailsPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundCustomSoundPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundDamageEventPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundDebugSamplePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundDeleteChatPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundDisconnectPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundDisguisedChatPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundEntityEventPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundEntityPositionSyncPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundExplodePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundForgetLevelChunkPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundGameEventPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundHorseScreenOpenPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundHurtAnimationPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundInitializeBorderPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundKeepAlivePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundLevelChunkPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundLevelChunkWithLightPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundLevelEventPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundLevelParticlesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundLightUpdatePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundLoginPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundMapItemDataPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundMerchantOffersPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundMoveEntityPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundMoveEntityPacketPos.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundMoveEntityPacketPosRot.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundMoveEntityPacketRot.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundMoveMinecartPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundMoveVehiclePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundOpenBookPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundOpenScreenPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundOpenSignEditorPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPingPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlaceGhostRecipePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerAbilitiesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerChatHeaderPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerChatPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerCombatEndPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerCombatEnterPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerCombatKillPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerCombatPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerInfoPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerInfoRemovePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerInfoUpdatePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerLookAtPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerPositionPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPlayerRotationPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundPongResponsePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundProjectilePowerPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRecipeBookAddPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRecipeBookRemovePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRecipeBookSettingsPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRecipePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRemoveEntitiesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRemoveEntityPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRemoveMobEffectPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundResourcePackPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundResetScorePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundResourcePackPopPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundResourcePackPushPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRespawnPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundRotateHeadPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSelectAdvancementsTabPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundServerDataPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundServerLinksPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetActionBarTextPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderCenterPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderLerpSizePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderSizePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderWarningDelayPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetBorderWarningDistancePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetCameraPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetCarriedItemPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetChunkCacheCenterPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetChunkCacheRadiusPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetCursorItemPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetDefaultSpawnPositionPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetDisplayChatPreviewPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetDisplayObjectivePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetEntityDataPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetEntityLinkPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetEntityMotionPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetEquipmentPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetExperiencePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetHealthPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetHeldSlotPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetObjectivePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetPassengersPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetPlayerInventoryPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetPlayerTeamPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetScorePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetSimulationDistancePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetSubtitleTextPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetTimePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetTitlesAnimationPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetTitlesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSetTitleTextPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundShowDialogPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSoundEntityPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSoundPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundStartConfigurationPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundStopSoundPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundStoreCookiePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundSystemChatPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTabListPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTagQueryPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTakeItemEntityPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTeleportEntityPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTestInstanceBlockStatusPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTickingStatePacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTickingStepPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTrackedWaypointPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundTransferPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundUpdateAdvancementsPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundUpdateAttributesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundUpdateMobEffectPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundUpdateRecipesPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundUpdateTagsPacket.hpp
    include/protocolCraft/Packets/Game/Clientbound/ClientboundUseBedPacket.hpp

    include/protocolCraft/Packets/Game/Serverbound/ServerboundAcceptTeleportationPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundBlockEntityTagQueryPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChangeDifficultyPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChangeGameModePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChatAckPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChatCommandSignedPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChatCommandPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChatPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChatPreviewPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChatSessionUpdatePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundChunkBatchReceivedPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundClientCommandPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundClientInformationPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundClientTickEndPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundCommandSuggestionPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundConfigurationAcknowledgedPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundContainerAckPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundContainerButtonClickPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundContainerClickPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundContainerClosePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundContainerSlotStateChangedPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundCookieResponsePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundCustomClickActionPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundCustomPayloadPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundDebugSampleSubscriptionPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundEditBookPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundEnchantItemPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundEntityTagQueryPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundInteractPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundJigsawGeneratePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundKeepAlivePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundLockDifficultyPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacketPos.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacketPosRot.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacketRot.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacketStatusOnly.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundMoveVehiclePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPaddleBoatPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPickItemFromBlockPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPickItemFromEntityPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPickItemPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPingRequestPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPlaceRecipePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPlayerAbilitiesPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPlayerActionPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPlayerCommandPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPlayerInputPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPlayerLoadedPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundPongPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundRecipeBookChangeSettingsPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundRecipeBookSeenRecipePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundRecipeBookUpdatePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundRenameItemPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundResourcePackPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSeenAdvancementsPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSelectBundleItemPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSelectTradePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSetBeaconPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSetCarriedItemPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSetCommandBlockPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSetCommandMinecartPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSetCreativeModeSlotPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSetJigsawBlockPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSetStructureBlockPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSetTestBlockPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSignUpdatePacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundSwingPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundTeleportToEntityPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundTestInstanceBlockActionPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundUseItemOnPacket.hpp
    include/protocolCraft/Packets/Game/Serverbound/ServerboundUseItemPacket.hpp


    include/protocolCraft/Packets/Status/Clientbound/ClientboundPongResponsePacket.hpp
    include/protocolCraft/Packets/Status/Clientbound/ClientboundStatusResponsePacket.hpp

    include/protocolCraft/Packets/Status/Serverbound/ServerboundPingRequestPacket.hpp
    include/protocolCraft/Packets/Status/Serverbound/ServerboundStatusRequestPacket.hpp


    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundClearDialogPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundCookieRequestPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundCustomPayloadPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundCustomReportDetailsPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundDisconnectPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundFinishConfigurationPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundKeepAlivePacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundPingPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundRegistryDataPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundResetChatPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundResourcePackPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundResourcePackPopConfigurationPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundResourcePackPushConfigurationPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundSelectKnownPacksPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundServerLinksPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundShowDialogPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundStoreCookiePacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundTransferPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundUpdateTagsPacket.hpp

    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundClientInformationPacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundCookieResponsePacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundCustomClickActionPacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundCustomPayloadPacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundFinishConfigurationPacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundKeepAlivePacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundPongPacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundResourcePackPacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundSelectKnownPacksPacket.hpp


    include/protocolCraft/Types/Advancement.hpp
    include/protocolCraft/Types/AdvancementDisplay.hpp
    include/protocolCraft/Types/AdvancementProgress.hpp
    include/protocolCraft/Types/BlockEntityInfo.hpp
    include/protocolCraft/Types/BlockEntityTag.hpp
    include/protocolCraft/Types/ChunkBiomeData.hpp
    include/protocolCraft/Types/ChunkPos.hpp
    include/protocolCraft/Types/ClientboundLevelChunkPacketData.hpp
    include/protocolCraft/Types/ClientboundLightUpdatePacketData.hpp
    include/protocolCraft/Types/ClientInformation.hpp
    include/protocolCraft/Types/CommonPlayerSpawnInfo.hpp
    include/protocolCraft/Types/CriterionProgress.hpp
    include/protocolCraft/Types/Either.hpp
    include/protocolCraft/Types/EntityModifierData.hpp
    include/protocolCraft/Types/EntityProperty.hpp
    include/protocolCraft/Types/Filterable.hpp
    include/protocolCraft/Types/GlobalPos.hpp
    include/protocolCraft/Types/Holder.hpp
    include/protocolCraft/Types/HolderSet.hpp
    include/protocolCraft/Types/Identifier.hpp
    include/protocolCraft/Types/KnownPack.hpp
    include/protocolCraft/Types/MapDecoration.hpp
    include/protocolCraft/Types/MinecartBehaviorMinecartStep.hpp
    include/protocolCraft/Types/NetworkPosition.hpp
    include/protocolCraft/Types/PackedRegistryEntry.hpp
    include/protocolCraft/Types/PlayerUpdate.hpp
    include/protocolCraft/Types/PositionMoveRotation.hpp
    include/protocolCraft/Types/Record.hpp
    include/protocolCraft/Types/SaltSignature.hpp
    include/protocolCraft/Types/ServerLinksUnstrustedEntry.hpp
    include/protocolCraft/Types/TestInstanceBlockEntityData.hpp

    include/protocolCraft/Types/Chat/Chat.hpp
    include/protocolCraft/Types/Chat/ChatMessageContent.hpp
    include/protocolCraft/Types/Chat/ChatSender.hpp
    include/protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp
    include/protocolCraft/Types/Chat/FilterMask.hpp
    include/protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp
    include/protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp
    include/protocolCraft/Types/Chat/NumberFormat.hpp
    include/protocolCraft/Types/Chat/PlayerChatMessage.hpp
    include/protocolCraft/Types/Chat/RemoteChatSessionData.hpp
    include/protocolCraft/Types/Chat/SignedMessageHeader.hpp
    include/protocolCraft/Types/Chat/SignedMessageBody.hpp

    include/protocolCraft/Types/CommandNode/BrigadierProperty.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyDouble.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyEntity.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyFloat.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyInteger.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyLong.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyNone.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyRange.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyResourceOrTag.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyScoreHolder.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyString.hpp
    include/protocolCraft/Types/CommandNode/BrigadierPropertyTime.hpp
    include/protocolCraft/Types/CommandNode/CommandNode.hpp

    include/protocolCraft/Types/Components/DataComponents.hpp
    include/protocolCraft/Types/Components/DataComponentType.hpp
    include/protocolCraft/Types/Components/DataComponentTypeAdventureModePredicate.hpp
    include/protocolCraft/Types/Components/DataComponentTypeArmorTrim.hpp
    include/protocolCraft/Types/Components/DataComponentTypeBannerPatternLayers.hpp
    include/protocolCraft/Types/Components/DataComponentTypeBlockItemStateProperties.hpp
    include/protocolCraft/Types/Components/DataComponentTypeBlocksAttacks.hpp
    include/protocolCraft/Types/Components/DataComponentTypeBoolean.hpp
    include/protocolCraft/Types/Components/DataComponentTypeBreakSound.hpp
    include/protocolCraft/Types/Components/DataComponentTypeBundleContents.hpp
    include/protocolCraft/Types/Components/DataComponentTypeChargedProjectiles.hpp
    include/protocolCraft/Types/Components/DataComponentTypeComponent.hpp
    include/protocolCraft/Types/Components/DataComponentTypeConsumable.hpp
    include/protocolCraft/Types/Components/DataComponentTypeCustomData.hpp
    include/protocolCraft/Types/Components/DataComponentTypeCustomModelData.hpp
    include/protocolCraft/Types/Components/DataComponentTypeDeathProtection.hpp
    include/protocolCraft/Types/Components/DataComponentTypeDefault.hpp
    include/protocolCraft/Types/Components/DataComponentTypeDyeColor.hpp
    include/protocolCraft/Types/Components/DataComponentTypeDyedItemColor.hpp
    include/protocolCraft/Types/Components/DataComponentTypeEquippable.hpp
    include/protocolCraft/Types/Components/DataComponentTypeFireworkExplosion.hpp
    include/protocolCraft/Types/Components/DataComponentTypeFireworks.hpp
    include/protocolCraft/Types/Components/DataComponentTypeFoodProperties.hpp
    include/protocolCraft/Types/Components/DataComponentTypeInstrument.hpp
    include/protocolCraft/Types/Components/DataComponentTypeInteger.hpp
    include/protocolCraft/Types/Components/DataComponentTypeItemAttributeModifiers.hpp
    include/protocolCraft/Types/Components/DataComponentTypeItemContainerContents.hpp
    include/protocolCraft/Types/Components/DataComponentTypeItemEnchantments.hpp
    include/protocolCraft/Types/Components/DataComponentTypeItemLore.hpp
    include/protocolCraft/Types/Components/DataComponentTypeJukeboxPlayable.hpp
    include/protocolCraft/Types/Components/DataComponentTypeListBeehiveBlockEntityOccupant.hpp
    include/protocolCraft/Types/Components/DataComponentTypeLodestoneTracker.hpp
    include/protocolCraft/Types/Components/DataComponentTypeMapId.hpp
    include/protocolCraft/Types/Components/DataComponentTypeMapItemColor.hpp
    include/protocolCraft/Types/Components/DataComponentTypeMapPostProcessing.hpp
    include/protocolCraft/Types/Components/DataComponentTypePotDecorations.hpp
    include/protocolCraft/Types/Components/DataComponentTypePaintingVariant.hpp
    include/protocolCraft/Types/Components/DataComponentTypePotionContents.hpp
    include/protocolCraft/Types/Components/DataComponentTypePotionDurationScale.hpp
    include/protocolCraft/Types/Components/DataComponentTypeProvidesTrimMaterial.hpp
    include/protocolCraft/Types/Components/DataComponentTypeRarity.hpp
    include/protocolCraft/Types/Components/DataComponentTypeRepairable.hpp
    include/protocolCraft/Types/Components/DataComponentTypeResolvableProfile.hpp
    include/protocolCraft/Types/Components/DataComponentTypeResourceLocation.hpp
    include/protocolCraft/Types/Components/DataComponentTypeSuspiciousStewEffects.hpp
    include/protocolCraft/Types/Components/DataComponentTypeTool.hpp
    include/protocolCraft/Types/Components/DataComponentTypeTooltipDisplay.hpp
    include/protocolCraft/Types/Components/DataComponentTypeUnbreakable.hpp
    include/protocolCraft/Types/Components/DataComponentTypeUnit.hpp
    include/protocolCraft/Types/Components/DataComponentTypeUseRemainder.hpp
    include/protocolCraft/Types/Components/DataComponentTypeVariantEnum.hpp
    include/protocolCraft/Types/Components/DataComponentTypeWeapon.hpp
    include/protocolCraft/Types/Components/DataComponentTypeUseCooldown.hpp
    include/protocolCraft/Types/Components/DataComponentTypeWritableBookContent.hpp
    include/protocolCraft/Types/Components/DataComponentTypeWrittenBookContent.hpp

    include/protocolCraft/Types/Components/Subtypes/AttributeModifier.hpp
    include/protocolCraft/Types/Components/Subtypes/BannerPatternLayer.hpp
    include/protocolCraft/Types/Components/Subtypes/BeehiveBlockEntityOccupant.hpp
    include/protocolCraft/Types/Components/Subtypes/BlockPredicate.hpp
    include/protocolCraft/Types/Components/Subtypes/DamageReduction.hpp
    include/protocolCraft/Types/Components/Subtypes/Instrument.hpp
    include/protocolCraft/Types/Components/Subtypes/ItemDamageFunction.hpp
    include/protocolCraft/Types/Components/Subtypes/JukeboxSong.hpp
    include/protocolCraft/Types/Components/Subtypes/MaterialAssetGroup.hpp
    include/protocolCraft/Types/Components/Subtypes/MobEffectInstance.hpp
    include/protocolCraft/Types/Components/Subtypes/MobEffectInstanceDetails.hpp
    include/protocolCraft/Types/Components/Subtypes/PaintingVariant.hpp
    include/protocolCraft/Types/Components/Subtypes/PossibleEffect.hpp
    include/protocolCraft/Types/Components/Subtypes/PropertyMatcher.hpp
    include/protocolCraft/Types/Components/Subtypes/StatePropertiesPredicate.hpp
    include/protocolCraft/Types/Components/Subtypes/SuspiciousStewEntry.hpp
    include/protocolCraft/Types/Components/Subtypes/ToolRule.hpp
    include/protocolCraft/Types/Components/Subtypes/TrimMaterial.hpp
    include/protocolCraft/Types/Components/Subtypes/TrimPattern.hpp

    include/protocolCraft/Types/Components/Subtypes/Matcher/ExactMatcher.hpp
    include/protocolCraft/Types/Components/Subtypes/Matcher/RangedMatcher.hpp

    include/protocolCraft/Types/Components/Subtypes/ConsumeEffects/ApplyStatusEffectsConsumeEffect.hpp
    include/protocolCraft/Types/Components/Subtypes/ConsumeEffects/ClearAllStatusEffectsConsumeEffect.hpp
    include/protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffect.hpp
    include/protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffectData.hpp
    include/protocolCraft/Types/Components/Subtypes/ConsumeEffects/PlaySoundConsumeEffect.hpp
    include/protocolCraft/Types/Components/Subtypes/ConsumeEffects/RemoveStatusEffectsConsumeEffect.hpp
    include/protocolCraft/Types/Components/Subtypes/ConsumeEffects/TeleportRandomlyConsumeEffect.hpp

    include/protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/DefaultDisplay.hpp
    include/protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/ItemAttributeModifiersDisplay.hpp
    include/protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/ItemAttributeModifiersDisplayData.hpp
    include/protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/ItemAttributeModifiersEntry.hpp
    include/protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/HiddenDisplay.hpp
    include/protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/OverrideDisplay.hpp

    include/protocolCraft/Types/GameProfile/GameProfile.hpp
    include/protocolCraft/Types/GameProfile/GameProfileProperty.hpp
    include/protocolCraft/Types/GameProfile/ProfilePublicKey.hpp

    include/protocolCraft/Types/Item/HashedSlot.hpp
    include/protocolCraft/Types/Item/ItemCost.hpp
    include/protocolCraft/Types/Item/MerchantOffer.hpp
    include/protocolCraft/Types/Item/Slot.hpp

    include/protocolCraft/Types/NBT/NBT.hpp
    include/protocolCraft/Types/NBT/Tag.hpp

    include/protocolCraft/Types/Particles/Particle.hpp
    include/protocolCraft/Types/Particles/ParticleOptions.hpp

    include/protocolCraft/Types/Particles/BlockParticleOptions.hpp
    include/protocolCraft/Types/Particles/ColorParticleOptions.hpp
    include/protocolCraft/Types/Particles/IconcrackParticleOptions.hpp
    include/protocolCraft/Types/Particles/DustColorTransitionOptions.hpp
    include/protocolCraft/Types/Particles/DustParticleOptions.hpp
    include/protocolCraft/Types/Particles/EmptyParticleOptions.hpp
    include/protocolCraft/Types/Particles/ItemParticleOptions.hpp
    include/protocolCraft/Types/Particles/SculkChargeParticleOptions.hpp
    include/protocolCraft/Types/Particles/ShriekParticleOptions.hpp
    include/protocolCraft/Types/Particles/TrailParticleOptions.hpp
    include/protocolCraft/Types/Particles/VibrationParticleOptions.hpp

    include/protocolCraft/Types/Recipes/CompositeSlotDisplay.hpp
    include/protocolCraft/Types/Recipes/FurnaceRecipeDisplay.hpp
    include/protocolCraft/Types/Recipes/Ingredient.hpp
    include/protocolCraft/Types/Recipes/ItemSlotDisplay.hpp
    include/protocolCraft/Types/Recipes/ItemStackSlotDisplay.hpp
    include/protocolCraft/Types/Recipes/Recipe.hpp
    include/protocolCraft/Types/Recipes/RecipeBookAddEntry.hpp
    include/protocolCraft/Types/Recipes/RecipeBookSettings.hpp
    include/protocolCraft/Types/Recipes/RecipeData.hpp
    include/protocolCraft/Types/Recipes/RecipeDataCraftingShaped.hpp
    include/protocolCraft/Types/Recipes/RecipeDataCraftingShapeless.hpp
    include/protocolCraft/Types/Recipes/RecipeDataSimpleCooking.hpp
    include/protocolCraft/Types/Recipes/RecipeDataSimpleCrafting.hpp
    include/protocolCraft/Types/Recipes/RecipeDataSingleItem.hpp
    include/protocolCraft/Types/Recipes/RecipeDataSmithing.hpp
    include/protocolCraft/Types/Recipes/RecipeDataSmithingTransform.hpp
    include/protocolCraft/Types/Recipes/RecipeDataSmithingTrim.hpp
    include/protocolCraft/Types/Recipes/RecipeDisplay.hpp
    include/protocolCraft/Types/Recipes/RecipeDisplayData.hpp
    include/protocolCraft/Types/Recipes/RecipeDisplayEntry.hpp
    include/protocolCraft/Types/Recipes/SelectableRecipe.hpp
    include/protocolCraft/Types/Recipes/SelectableRecipeSingleInputEntry.hpp
    include/protocolCraft/Types/Recipes/ShapedCraftingRecipeDisplay.hpp
    include/protocolCraft/Types/Recipes/ShapelessCraftingRecipeDisplay.hpp
    include/protocolCraft/Types/Recipes/SlotDisplay.hpp
    include/protocolCraft/Types/Recipes/SlotDisplayData.hpp
    include/protocolCraft/Types/Recipes/SlotDisplayDataEmpty.hpp
    include/protocolCraft/Types/Recipes/SmithingRecipeDisplay.hpp
    include/protocolCraft/Types/Recipes/SmithingTrimDemoSlotDisplay.hpp
    include/protocolCraft/Types/Recipes/StonecutterRecipeDisplay.hpp
    include/protocolCraft/Types/Recipes/TagSlotDisplay.hpp
    include/protocolCraft/Types/Recipes/WithRemainderSlotDisplay.hpp

    include/protocolCraft/Types/Sound/SoundEvent.hpp

    include/protocolCraft/Types/Vibrations/BlockPositionSource.hpp
    include/protocolCraft/Types/Vibrations/EntityPositionSource.hpp
    include/protocolCraft/Types/Vibrations/PositionSource.hpp
    include/protocolCraft/Types/Vibrations/VibrationPath.hpp

    include/protocolCraft/Types/Waypoints/AzimuthWaypoint.hpp
    include/protocolCraft/Types/Waypoints/ChunkWaypoint.hpp
    include/protocolCraft/Types/Waypoints/EmptyWaypoint.hpp
    include/protocolCraft/Types/Waypoints/TrackedWaypoint.hpp
    include/protocolCraft/Types/Waypoints/TrackedWaypointData.hpp
    include/protocolCraft/Types/Waypoints/Vec3iWaypoint.hpp
    include/protocolCraft/Types/Waypoints/WaypointIcon.hpp

    include/protocolCraft/Utilities/AutoSerializedMacros.hpp
    include/protocolCraft/Utilities/AutoSerializedToJson.hpp
    include/protocolCraft/Utilities/ConstexprStrProcessing.hpp
    include/protocolCraft/Utilities/CustomType.hpp
    include/protocolCraft/Utilities/GZip.hpp
    include/protocolCraft/Utilities/Json.hpp
    include/protocolCraft/Utilities/RecursiveWrapper.hpp
    include/protocolCraft/Utilities/Templates.hpp

    include/protocolCraft/Utilities/Plugins/PluginLoader.hpp
    include/protocolCraft/Utilities/Plugins/PluginObject.hpp
)

set(protocolCraft_SRC
    src/BasePacket.cpp
    src/BinaryReadWrite.cpp
    src/NetworkType.cpp
    src/PacketFactory.cpp

    src/Types/Chat/Chat.cpp

    src/Types/CommandNode/BrigadierProperty.cpp

    src/Types/Components/DataComponents.cpp

    src/Types/Components/Subtypes/ConsumeEffects/ConsumeEffect.cpp

    src/Types/Components/Subtypes/ItemAttributeModifiers/Display.cpp

    src/Types/NBT/NBT.cpp
    src/Types/NBT/Tag.cpp

    src/Types/Particles/Particle.cpp

    src/Types/Recipes/Recipe.cpp
    src/Types/Recipes/RecipeDisplay.cpp
    src/Types/Recipes/SlotDisplay.cpp

    src/Types/Vibrations/PositionSource.cpp

    src/Types/Waypoints/TrackedWaypoint.cpp

    src/Utilities/GZip.cpp
    src/Utilities/Json.cpp

    src/Utilities/Plugins/PluginLoader.cpp
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

if(PROTOCOLCRAFT_STATIC)
    add_library(protocolCraft STATIC ${protocolCraft_SRC} ${protocolCraft_PUBLIC_HDR})
else()
    add_library(protocolCraft SHARED ${protocolCraft_SRC} ${protocolCraft_PUBLIC_HDR})
endif(PROTOCOLCRAFT_STATIC)
set_property(TARGET protocolCraft PROPERTY CXX_STANDARD 17)
set_property(TARGET protocolCraft PROPERTY POSITION_INDEPENDENT_CODE ON)
set_target_properties(protocolCraft PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(protocolCraft PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")
# Add special $ORIGIN to rpath so Linux can find shared libraries in same folder
set_target_properties(protocolCraft PROPERTIES INSTALL_RPATH "$ORIGIN")

if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/lib")
else()
    set_target_properties(protocolCraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(protocolCraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/lib")
endif(MSVC)

if (MSVC)
    target_compile_options(protocolCraft PRIVATE "/bigobj")
    set_target_properties(protocolCraft PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif (MSVC)

# Set version
target_compile_definitions(protocolCraft PUBLIC PROTOCOL_VERSION=${PROTOCOL_VERSION})

# Add include folders
target_include_directories(protocolCraft
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
)

if(BOTCRAFT_COMPRESSION)
    target_link_libraries(protocolCraft PRIVATE ZLIB::ZLIB)
    target_compile_definitions(protocolCraft PRIVATE USE_COMPRESSION=1)
endif(BOTCRAFT_COMPRESSION)

if (NOT PROTOCOLCRAFT_STATIC)
    # Add DL lib for linux compilation
    target_link_libraries(protocolCraft PUBLIC ${CMAKE_DL_LIBS})
endif()

# Setup detailed parsing preprocessor variable
if(PROTOCOLCRAFT_DETAILED_PARSING)
    target_compile_definitions(protocolCraft PUBLIC PROTOCOLCRAFT_DETAILED_PARSING=1)
endif(PROTOCOLCRAFT_DETAILED_PARSING)

# Installation stuff
include(GNUInstallDirs)

install(TARGETS protocolCraft
    EXPORT protocolCraft-targets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/protocolCraft"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(EXPORT protocolCraft-targets
    # lowercase as required by find_package
    FILE protocolcraft-targets.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/protocolCraft"
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/protocolCraft-config.cmake.in"
    # lowercase as required by find_package
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/protocolcraft-config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/protocolCraft"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/protocolcraft-config.cmake"
    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/protocolCraft"
)

export(EXPORT protocolCraft-targets
    # lowercase as required by find_package
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/protocolcraft-targets.cmake"
)
