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

    include/protocolCraft/Packets/Handshaking/Serverbound/ServerboundClientIntentionPacket.hpp


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


    include/protocolCraft/Packets/Play/Clientbound/ClientboundAddEntityPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundAddExperienceOrbPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundAddGlobalEntityPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundAddMobPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundAddPaintingPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundAddPlayerPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundAddVibrationSignalPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundAnimatePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundAwardStatsPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundBlockBreakAckPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundBlockChangedAckPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundBlockDestructionPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundBlockEntityDataPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundBlockEventPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundBlockUpdatePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundBossEventPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundBundlePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundChangeDifficultyPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundChatPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundChatPreviewPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundChunkBatchFinishedPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundChunkBatchStartPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundChunksBiomesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundClearTitlesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundCommandsPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundCommandSuggestionsPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundContainerAckPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundContainerClosePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundContainerSetContentPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundContainerSetDataPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundContainerSetSlotPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundCookieRequestPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundCooldownPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundCustomChatCompletionsPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundCustomPayloadPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundCustomReportDetailsPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundCustomSoundPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundDamageEventPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundDebugSamplePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundDeleteChatPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundDisconnectPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundDisguisedChatPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundEntityEventPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundEntityPositionSyncPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundExplodePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundForgetLevelChunkPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundGameEventPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundHorseScreenOpenPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundHurtAnimationPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundInitializeBorderPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundKeepAlivePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundLevelChunkPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundLevelChunkWithLightPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundLevelEventPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundLevelParticlesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundLightUpdatePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundLoginPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundMapItemDataPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundMerchantOffersPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundMoveEntityPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundMoveEntityPacketPos.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundMoveEntityPacketPosRot.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundMoveEntityPacketRot.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundMoveMinecartPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundMoveVehiclePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundOpenBookPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundOpenScreenPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundOpenSignEditorPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPingPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlaceGhostRecipePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerAbilitiesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerChatHeaderPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerChatPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerCombatEndPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerCombatEnterPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerCombatKillPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerCombatPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerInfoPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerInfoRemovePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerInfoUpdatePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerLookAtPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerPositionPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPlayerRotationPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundPongResponsePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundProjectilePowerPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRecipeBookAddPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRecipeBookRemovePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRecipeBookSettingsPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRecipePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRemoveEntitiesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRemoveEntityPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRemoveMobEffectPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundResourcePackPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundResetScorePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundResourcePackPopPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundResourcePackPushPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRespawnPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundRotateHeadPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSelectAdvancementsTabPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundServerDataPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundServerLinksPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetActionBarTextPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetBorderCenterPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetBorderLerpSizePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetBorderPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetBorderSizePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetBorderWarningDelayPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetBorderWarningDistancePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetCameraPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetCarriedItemPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetChunkCacheCenterPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetChunkCacheRadiusPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetCursorItemPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetDefaultSpawnPositionPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetDisplayChatPreviewPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetDisplayObjectivePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetEntityDataPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetEntityLinkPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetEntityMotionPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetEquipmentPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetExperiencePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetHealthPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetHeldSlotPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetObjectivePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetPassengersPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetPlayerInventoryPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetPlayerTeamPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetScorePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetSimulationDistancePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetSubtitleTextPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetTimePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetTitlesAnimationPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetTitlesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSetTitleTextPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSoundEntityPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSoundPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundStartConfigurationPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundStopSoundPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundStoreCookiePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundSystemChatPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundTabListPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundTagQueryPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundTakeItemEntityPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundTeleportEntityPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundTestInstanceBlockStatusPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundTickingStatePacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundTickingStepPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundTransferPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundUpdateAdvancementsPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundUpdateAttributesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundUpdateMobEffectPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundUpdateRecipesPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundUpdateTagsPacket.hpp
    include/protocolCraft/Packets/Play/Clientbound/ClientboundUseBedPacket.hpp

    include/protocolCraft/Packets/Play/Serverbound/ServerboundAcceptTeleportationPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundBlockEntityTagQueryPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundChangeDifficultyPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundChatAckPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundChatCommandSignedPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundChatCommandPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundChatPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundChatPreviewPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundChatSessionUpdatePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundChunkBatchReceivedPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundClientCommandPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundClientInformationPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundClientTickEndPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundCommandSuggestionPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundConfigurationAcknowledgedPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundContainerAckPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundContainerButtonClickPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundContainerClickPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundContainerClosePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundContainerSlotStateChangedPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundCookieResponsePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundCustomPayloadPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundDebugSampleSubscriptionPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundEditBookPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundEnchantItemPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundEntityTagQueryPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundInteractPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundJigsawGeneratePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundKeepAlivePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundLockDifficultyPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundMovePlayerPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundMovePlayerPacketPos.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundMovePlayerPacketPosRot.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundMovePlayerPacketRot.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundMovePlayerPacketStatusOnly.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundMoveVehiclePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPaddleBoatPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPickItemFromBlockPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPickItemFromEntityPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPickItemPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPingRequestPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPlaceRecipePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPlayerAbilitiesPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPlayerActionPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPlayerCommandPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPlayerInputPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPlayerLoadedPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundPongPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundRecipeBookChangeSettingsPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundRecipeBookSeenRecipePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundRecipeBookUpdatePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundRenameItemPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundResourcePackPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSeenAdvancementsPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSelectBundleItemPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSelectTradePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSetBeaconPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSetCarriedItemPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSetCommandBlockPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSetCommandMinecartPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSetCreativeModeSlotPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSetJigsawBlockPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSetStructureBlockPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSetTestBlockPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSignUpdatePacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundSwingPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundTeleportToEntityPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundTestInstanceBlockActionPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundUseItemOnPacket.hpp
    include/protocolCraft/Packets/Play/Serverbound/ServerboundUseItemPacket.hpp


    include/protocolCraft/Packets/Status/Clientbound/ClientboundPongResponsePacket.hpp
    include/protocolCraft/Packets/Status/Clientbound/ClientboundStatusResponsePacket.hpp

    include/protocolCraft/Packets/Status/Serverbound/ServerboundPingRequestPacket.hpp
    include/protocolCraft/Packets/Status/Serverbound/ServerboundStatusRequestPacket.hpp


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
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundStoreCookiePacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundTransferPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp
    include/protocolCraft/Packets/Configuration/Clientbound/ClientboundUpdateTagsPacket.hpp

    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundClientInformationPacket.hpp
    include/protocolCraft/Packets/Configuration/Serverbound/ServerboundCookieResponsePacket.hpp
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
    include/protocolCraft/Types/Components/Subtypes/ItemAttributeModifiersEntry.hpp
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

    src/Types/NBT/NBT.cpp
    src/Types/NBT/Tag.cpp

    src/Types/Particles/Particle.cpp

    src/Types/Recipes/Recipe.cpp
    src/Types/Recipes/RecipeDisplay.cpp
    src/Types/Recipes/SlotDisplay.cpp

    src/Types/Vibrations/PositionSource.cpp

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
