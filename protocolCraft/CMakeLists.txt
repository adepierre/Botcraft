project(protocolCraft)

set(protocolCraft_PUBLIC_HDR
    include/protocolCraft/AllClientboundMessages.hpp
    include/protocolCraft/AllMessages.hpp
    include/protocolCraft/AllServerboundMessages.hpp
    include/protocolCraft/BaseMessage.hpp
    include/protocolCraft/BinaryReadWrite.hpp
    include/protocolCraft/enums.hpp
    include/protocolCraft/GenericHandler.hpp
    include/protocolCraft/Handler.hpp
    include/protocolCraft/Message.hpp
    include/protocolCraft/MessageFactory.hpp
    include/protocolCraft/NetworkType.hpp

    include/protocolCraft/Messages/Handshaking/Serverbound/ServerboundClientIntentionPacket.hpp


    include/protocolCraft/Messages/Login/Clientbound/ClientboundCookieRequestPacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundCustomQueryPacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundGameProfilePacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundHelloPacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundLoginCompressionPacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundLoginDisconnectPacket.hpp
    include/protocolCraft/Messages/Login/Clientbound/ClientboundLoginFinishedPacket.hpp

    include/protocolCraft/Messages/Login/Serverbound/ServerboundCookieResponsePacket.hpp
    include/protocolCraft/Messages/Login/Serverbound/ServerboundCustomQueryAnswerPacket.hpp
    include/protocolCraft/Messages/Login/Serverbound/ServerboundCustomQueryPacket.hpp
    include/protocolCraft/Messages/Login/Serverbound/ServerboundHelloPacket.hpp
    include/protocolCraft/Messages/Login/Serverbound/ServerboundKeyPacket.hpp
    include/protocolCraft/Messages/Login/Serverbound/ServerboundLoginAcknowledgedPacket.hpp


    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddExperienceOrbPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddGlobalEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddMobPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddPaintingPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddPlayerPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAddVibrationSignalPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAnimatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundAwardStatsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockBreakAckPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockChangedAckPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockDestructionPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockEntityDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBlockUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBossEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundBundlePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundChangeDifficultyPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundChatPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundChatPreviewPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundChunkBatchFinishedPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundChunkBatchStartPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundChunksBiomesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundClearTitlesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCommandsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCommandSuggestionsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerAckPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerClosePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetContentPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundContainerSetSlotPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCookieRequestPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCooldownPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCustomChatCompletionsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCustomPayloadPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCustomReportDetailsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundCustomSoundPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundDamageEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundDebugSamplePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundDeleteChatPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundDisconnectPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundDisguisedChatPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundEntityEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundEntityPositionSyncPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundExplodePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundForgetLevelChunkPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundGameEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundHorseScreenOpenPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundHurtAnimationPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundInitializeBorderPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundKeepAlivePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLevelChunkWithLightPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLevelEventPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLevelParticlesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLightUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundLoginPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMapItemDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMerchantOffersPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketPos.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketPosRot.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveEntityPacketRot.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveMinecartPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundMoveVehiclePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundOpenBookPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundOpenScreenPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundOpenSignEditorPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPingPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlaceGhostRecipePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerAbilitiesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerChatHeaderPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerChatPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatEndPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatEnterPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatKillPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerCombatPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoRemovePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerInfoUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerLookAtPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerPositionPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPlayerRotationPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundPongResponsePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundProjectilePowerPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRecipeBookAddPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRecipeBookRemovePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRecipeBookSettingsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRecipePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntitiesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRemoveEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRemoveMobEffectPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundResetScorePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPopPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundResourcePackPushPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRespawnPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundRotateHeadPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSectionBlocksUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSelectAdvancementsTabPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundServerDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundServerLinksPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetActionBarTextPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderCenterPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderLerpSizePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderSizePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderWarningDelayPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetBorderWarningDistancePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetCameraPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetCarriedItemPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheCenterPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetChunkCacheRadiusPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetCursorItemPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetDefaultSpawnPositionPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetDisplayChatPreviewPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetDisplayObjectivePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityDataPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityLinkPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetEntityMotionPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetEquipmentPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetExperiencePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetHealthPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetHeldSlotPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetObjectivePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetPassengersPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetPlayerInventoryPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetPlayerTeamPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetScorePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetSimulationDistancePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetSubtitleTextPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetTimePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetTitlesAnimationPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetTitlesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSetTitleTextPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSoundEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSoundPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundStartConfigurationPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundStopSoundPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundStoreCookiePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundSystemChatPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTabListPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTagQueryPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTakeItemEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTeleportEntityPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTickingStatePacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTickingStepPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundTransferPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAdvancementsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateAttributesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateMobEffectPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateRecipesPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUpdateTagsPacket.hpp
    include/protocolCraft/Messages/Play/Clientbound/ClientboundUseBedPacket.hpp

    include/protocolCraft/Messages/Play/Serverbound/ServerboundAcceptTeleportationPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundBlockEntityTagQueryPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChangeDifficultyPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChatAckPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChatCommandSignedPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChatCommandPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChatPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChatPreviewPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChatSessionUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundChunkBatchReceivedPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundClientCommandPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundClientInformationPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundClientTickEndPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundCommandSuggestionPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundConfigurationAcknowledgedPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundContainerAckPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundContainerButtonClickPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundContainerClickPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundContainerClosePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundContainerSlotStateChangedPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundCookieResponsePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundCustomPayloadPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundDebugSampleSubscriptionPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundEditBookPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundEnchantItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundEntityTagQueryPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundInteractPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundJigsawGeneratePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundKeepAlivePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundLockDifficultyPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPos.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPosRot.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketRot.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketStatusOnly.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundMoveVehiclePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPaddleBoatPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPickItemFromBlockPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPickItemFromEntityPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPickItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPingRequestPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlaceRecipePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerAbilitiesPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerActionPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerCommandPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerInputPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPlayerLoadedPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundPongPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookChangeSettingsPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookSeenRecipePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundRenameItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundResourcePackPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSeenAdvancementsPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSelectBundleItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSelectTradePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetBeaconPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetCarriedItemPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandBlockPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandMinecartPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetCreativeModeSlotPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetJigsawBlockPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSetStructureBlockPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSignUpdatePacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundSwingPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundTeleportToEntityPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundUseItemOnPacket.hpp
    include/protocolCraft/Messages/Play/Serverbound/ServerboundUseItemPacket.hpp


    include/protocolCraft/Messages/Status/Clientbound/ClientboundPongResponsePacket.hpp
    include/protocolCraft/Messages/Status/Clientbound/ClientboundStatusResponsePacket.hpp

    include/protocolCraft/Messages/Status/Serverbound/ServerboundPingRequestPacket.hpp
    include/protocolCraft/Messages/Status/Serverbound/ServerboundStatusRequestPacket.hpp


    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundCookieRequestPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundCustomPayloadPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundCustomReportDetailsPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundDisconnectPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundFinishConfigurationPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundKeepAlivePacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundPingPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundRegistryDataPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundResetChatPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPopConfigurationPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundResourcePackPushConfigurationPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundSelectKnownPacksPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundServerLinksPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundStoreCookiePacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundTransferPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundUpdateEnabledFeaturesPacket.hpp
    include/protocolCraft/Messages/Configuration/Clientbound/ClientboundUpdateTagsPacket.hpp

    include/protocolCraft/Messages/Configuration/Serverbound/ServerboundClientInformationPacket.hpp
    include/protocolCraft/Messages/Configuration/Serverbound/ServerboundCookieResponsePacket.hpp
    include/protocolCraft/Messages/Configuration/Serverbound/ServerboundCustomPayloadPacket.hpp
    include/protocolCraft/Messages/Configuration/Serverbound/ServerboundFinishConfigurationPacket.hpp
    include/protocolCraft/Messages/Configuration/Serverbound/ServerboundKeepAlivePacket.hpp
    include/protocolCraft/Messages/Configuration/Serverbound/ServerboundPongPacket.hpp
    include/protocolCraft/Messages/Configuration/Serverbound/ServerboundResourcePackPacket.hpp
    include/protocolCraft/Messages/Configuration/Serverbound/ServerboundSelectKnownPacksPacket.hpp


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
    include/protocolCraft/Types/Components/DataComponentTypeBoolean.hpp
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
    include/protocolCraft/Types/Components/DataComponentTypeHolderInstrument.hpp
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
    include/protocolCraft/Types/Components/DataComponentTypePotionContents.hpp
    include/protocolCraft/Types/Components/DataComponentTypeRarity.hpp
    include/protocolCraft/Types/Components/DataComponentTypeRepairable.hpp
    include/protocolCraft/Types/Components/DataComponentTypeResolvableProfile.hpp
    include/protocolCraft/Types/Components/DataComponentTypeResourceLocation.hpp
    include/protocolCraft/Types/Components/DataComponentTypeSuspiciousStewEffects.hpp
    include/protocolCraft/Types/Components/DataComponentTypeTool.hpp
    include/protocolCraft/Types/Components/DataComponentTypeUnbreakable.hpp
    include/protocolCraft/Types/Components/DataComponentTypeUnit.hpp
    include/protocolCraft/Types/Components/DataComponentTypeUseRemainder.hpp
    include/protocolCraft/Types/Components/DataComponentTypeUseCooldown.hpp
    include/protocolCraft/Types/Components/DataComponentTypeWritableBookContent.hpp
    include/protocolCraft/Types/Components/DataComponentTypeWrittenBookContent.hpp

    include/protocolCraft/Types/Components/Subtypes/AttributeModifier.hpp
    include/protocolCraft/Types/Components/Subtypes/BannerPatternLayer.hpp
    include/protocolCraft/Types/Components/Subtypes/BlockPredicate.hpp
    include/protocolCraft/Types/Components/Subtypes/ItemAttributeModifiersEntry.hpp
    include/protocolCraft/Types/Components/Subtypes/MobEffectInstance.hpp
    include/protocolCraft/Types/Components/Subtypes/MobEffectInstanceDetails.hpp
    include/protocolCraft/Types/Components/Subtypes/PossibleEffect.hpp
    include/protocolCraft/Types/Components/Subtypes/PropertyMatcher.hpp
    include/protocolCraft/Types/Components/Subtypes/StatePropertiesPredicate.hpp
    include/protocolCraft/Types/Components/Subtypes/SuspiciousStewEntry.hpp
    include/protocolCraft/Types/Components/Subtypes/ToolRule.hpp

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
    src/BaseMessage.cpp
    src/BinaryReadWrite.cpp
    src/MessageFactory.cpp
    src/NetworkType.cpp

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
