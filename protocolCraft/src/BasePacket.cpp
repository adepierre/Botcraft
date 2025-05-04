#include "protocolCraft/AllClientboundPackets.hpp"
#include "protocolCraft/AllServerboundPackets.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Handler.hpp"

namespace ProtocolCraft
{
    template<typename TDerived>
    int BasePacket<TDerived>::GetId() const
    {
        if constexpr (Internal::tuple_contains_type<TDerived, AllClientboundPlayPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllClientboundPlayPackets>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundPlayPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundPlayPackets>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllClientboundStatusPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllClientboundStatusPackets>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundStatusPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundStatusPackets>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllClientboundLoginPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllClientboundLoginPackets>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundLoginPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundLoginPackets>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundHandshakingPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundHandshakingPackets>;
        }
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundConfigurationPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundConfigurationPackets>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllClientboundConfigurationPackets>)
        {
            return Internal::get_tuple_index<TDerived, AllClientboundConfigurationPackets>;
        }
#endif
        else
        {
            static_assert(Internal::dependant_false<TDerived>, "Trying to define a packet which is not in protocol tuples");
        }
    }

    template <typename TDerived>
    void BasePacket<TDerived>::DispatchImpl(Handler* handler)
    {
        handler->Handle(static_cast<TDerived&>(*this));
    }

    // Explicit instantiation for each clientbound packet class

    // Login clientbound
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_PACKET_CLASS(ClientboundCookieRequestLoginPacket);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ClientboundCustomQueryPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundLoginDisconnectPacket);
    DEFINE_PACKET_CLASS(ClientboundHelloPacket);
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    DEFINE_PACKET_CLASS(ClientboundGameProfilePacket);
#else
    DEFINE_PACKET_CLASS(ClientboundLoginFinishedPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundLoginCompressionPacket);

    // Status clientbound
    DEFINE_PACKET_CLASS(ClientboundStatusResponsePacket);
    DEFINE_PACKET_CLASS(ClientboundPongResponseStatusPacket);

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    // Configuration clientbound
    DEFINE_PACKET_CLASS(ClientboundCustomPayloadConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundDisconnectConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundFinishConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundKeepAliveConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundPingConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundRegistryDataPacket);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    DEFINE_PACKET_CLASS(ClientboundResourcePackConfigurationPacket);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    DEFINE_PACKET_CLASS(ClientboundResourcePackPopConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundResourcePackPushConfigurationPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundUpdateEnabledFeaturesPacket);
    DEFINE_PACKET_CLASS(ClientboundUpdateTagsConfigurationPacket);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_PACKET_CLASS(ClientboundCookieRequestConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundResetChatPacket);
    DEFINE_PACKET_CLASS(ClientboundStoreCookieConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundSelectKnownPacksPacket);
    DEFINE_PACKET_CLASS(ClientboundTransferConfigurationPacket);
#endif
#if PROTOCOL_VERSION > 766 /* > 1.21 */
    DEFINE_PACKET_CLASS(ClientboundCustomReportDetailsConfigurationPacket);
    DEFINE_PACKET_CLASS(ClientboundServerLinksConfigurationPacket);
#endif
#endif

    // Play clientbound
    DEFINE_PACKET_CLASS(ClientboundUpdateAdvancementsPacket);
    DEFINE_PACKET_CLASS(ClientboundSetEntityLinkPacket);
    DEFINE_PACKET_CLASS(ClientboundBlockEventPacket);
    DEFINE_PACKET_CLASS(ClientboundBlockDestructionPacket);
    DEFINE_PACKET_CLASS(ClientboundBlockUpdatePacket);
    DEFINE_PACKET_CLASS(ClientboundBossEventPacket);
    DEFINE_PACKET_CLASS(ClientboundSetCameraPacket);
    DEFINE_PACKET_CLASS(ClientboundContainerClosePacket);
    DEFINE_PACKET_CLASS(ClientboundTakeItemEntityPacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_PACKET_CLASS(ClientboundPlayerCombatPacket);
#endif
#if PROTOCOL_VERSION == 755 /* 1.17 */
    DEFINE_PACKET_CLASS(ClientboundRemoveEntityPacket);
#else
    DEFINE_PACKET_CLASS(ClientboundRemoveEntitiesPacket);
#endif
#if PROTOCOL_VERSION > 345 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ClientboundCommandsPacket);
#endif
#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ClientboundUpdateRecipesPacket);
#endif
#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ClientboundPlayerLookAtPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundChangeDifficultyPacket);
    DEFINE_PACKET_CLASS(ClientboundMapItemDataPacket);
    DEFINE_PACKET_CLASS(ClientboundSectionBlocksUpdatePacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_PACKET_CLASS(ClientboundContainerAckPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundGameEventPacket);
    DEFINE_PACKET_CLASS(ClientboundPlaceGhostRecipePacket);
    DEFINE_PACKET_CLASS(ClientboundDisconnectPacket);
    DEFINE_PACKET_CLASS(ClientboundSetDisplayObjectivePacket);
    DEFINE_PACKET_CLASS(ClientboundForgetLevelChunkPacket);
    DEFINE_PACKET_CLASS(ClientboundKeepAlivePacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_PACKET_CLASS(ClientboundCustomSoundPacket);
#endif
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ClientboundTagQueryPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundOpenSignEditorPacket);
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ClientboundHorseScreenOpenPacket);
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ClientboundOpenBookPacket);
#endif
#if PROTOCOL_VERSION < 757 /* < 1.18 */
    DEFINE_PACKET_CLASS(ClientboundLevelChunkPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundLoginPacket);
    DEFINE_PACKET_CLASS(ClientboundLevelEventPacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_PACKET_CLASS(ClientboundMoveEntityPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundAnimatePacket);
    DEFINE_PACKET_CLASS(ClientboundSetEquipmentPacket);
    DEFINE_PACKET_CLASS(ClientboundUpdateMobEffectPacket);
    DEFINE_PACKET_CLASS(ClientboundRotateHeadPacket);
    DEFINE_PACKET_CLASS(ClientboundMoveEntityPacketPos);
    DEFINE_PACKET_CLASS(ClientboundMoveEntityPacketPosRot);
    DEFINE_PACKET_CLASS(ClientboundMoveEntityPacketRot);
    DEFINE_PACKET_CLASS(ClientboundSetEntityDataPacket);
    DEFINE_PACKET_CLASS(ClientboundUpdateAttributesPacket);
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ClientboundSoundEntityPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundEntityEventPacket);
    DEFINE_PACKET_CLASS(ClientboundSetEntityMotionPacket);
    DEFINE_PACKET_CLASS(ClientboundExplodePacket);
    DEFINE_PACKET_CLASS(ClientboundLevelParticlesPacket);
    DEFINE_PACKET_CLASS(ClientboundPlayerPositionPacket);
    DEFINE_PACKET_CLASS(ClientboundSetHealthPacket);
    DEFINE_PACKET_CLASS(ClientboundTeleportEntityPacket);
    DEFINE_PACKET_CLASS(ClientboundPlayerAbilitiesPacket);
    DEFINE_PACKET_CLASS(ClientboundSetTimePacket);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_PACKET_CLASS(ClientboundChatPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundRespawnPacket);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ClientboundLightUpdatePacket);
#endif
#if PROTOCOL_VERSION > 493 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_PACKET_CLASS(ClientboundBlockBreakAckPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundBlockEntityDataPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_PACKET_CLASS(ClientboundPlayerInfoPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundTabListPacket);
    DEFINE_PACKET_CLASS(ClientboundCustomPayloadPacket);
    DEFINE_PACKET_CLASS(ClientboundRemoveMobEffectPacket);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    DEFINE_PACKET_CLASS(ClientboundResourcePackPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundSetObjectivePacket);
    DEFINE_PACKET_CLASS(ClientboundSelectAdvancementsTabPacket);
    DEFINE_PACKET_CLASS(ClientboundSetExperiencePacket);
    DEFINE_PACKET_CLASS(ClientboundContainerSetSlotPacket);
    DEFINE_PACKET_CLASS(ClientboundCooldownPacket);
    DEFINE_PACKET_CLASS(ClientboundSetPassengersPacket);
    DEFINE_PACKET_CLASS(ClientboundSoundPacket);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    DEFINE_PACKET_CLASS(ClientboundAddExperienceOrbPacket);
#endif
#if PROTOCOL_VERSION < 721 /* < 1.16 */
    DEFINE_PACKET_CLASS(ClientboundAddGlobalEntityPacket);
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_PACKET_CLASS(ClientboundAddMobPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundAddEntityPacket);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_PACKET_CLASS(ClientboundAddPaintingPacket);
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    DEFINE_PACKET_CLASS(ClientboundAddPlayerPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundSetDefaultSpawnPositionPacket);
    DEFINE_PACKET_CLASS(ClientboundAwardStatsPacket);
#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ClientboundStopSoundPacket);
#endif
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ClientboundUpdateTagsPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundCommandSuggestionsPacket);
    DEFINE_PACKET_CLASS(ClientboundSetPlayerTeamPacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_PACKET_CLASS(ClientboundSetTitlesPacket);
#endif
#if PROTOCOL_VERSION < 461 /* < 1.14 */
    DEFINE_PACKET_CLASS(ClientboundUseBedPacket);
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ClientboundMerchantOffersPacket);
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    DEFINE_PACKET_CLASS(ClientboundRecipePacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundSetScorePacket);
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ClientboundSetChunkCacheCenterPacket);
    DEFINE_PACKET_CLASS(ClientboundSetChunkCacheRadiusPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundMoveVehiclePacket);
    DEFINE_PACKET_CLASS(ClientboundContainerSetContentPacket);
    DEFINE_PACKET_CLASS(ClientboundContainerSetDataPacket);
    DEFINE_PACKET_CLASS(ClientboundOpenScreenPacket);
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    DEFINE_PACKET_CLASS(ClientboundSetCarriedItemPacket);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_PACKET_CLASS(ClientboundSetBorderPacket);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_PACKET_CLASS(ClientboundAddVibrationSignalPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundClearTitlesPacket);
    DEFINE_PACKET_CLASS(ClientboundInitializeBorderPacket);
    DEFINE_PACKET_CLASS(ClientboundPingPacket);
    DEFINE_PACKET_CLASS(ClientboundPlayerCombatEndPacket);
    DEFINE_PACKET_CLASS(ClientboundPlayerCombatEnterPacket);
    DEFINE_PACKET_CLASS(ClientboundPlayerCombatKillPacket);
    DEFINE_PACKET_CLASS(ClientboundSetActionBarTextPacket);
    DEFINE_PACKET_CLASS(ClientboundSetBorderCenterPacket);
    DEFINE_PACKET_CLASS(ClientboundSetBorderLerpSizePacket);
    DEFINE_PACKET_CLASS(ClientboundSetBorderSizePacket);
    DEFINE_PACKET_CLASS(ClientboundSetBorderWarningDelayPacket);
    DEFINE_PACKET_CLASS(ClientboundSetBorderWarningDistancePacket);
    DEFINE_PACKET_CLASS(ClientboundSetSubtitleTextPacket);
    DEFINE_PACKET_CLASS(ClientboundSetTitleTextPacket);
    DEFINE_PACKET_CLASS(ClientboundSetTitlesAnimationPacket);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    DEFINE_PACKET_CLASS(ClientboundLevelChunkWithLightPacket);
    DEFINE_PACKET_CLASS(ClientboundSetSimulationDistancePacket);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_PACKET_CLASS(ClientboundBlockChangedAckPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_PACKET_CLASS(ClientboundChatPreviewPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundPlayerChatPacket);
    DEFINE_PACKET_CLASS(ClientboundServerDataPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_PACKET_CLASS(ClientboundSetDisplayChatPreviewPacket);
#endif
    DEFINE_PACKET_CLASS(ClientboundSystemChatPacket);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    DEFINE_PACKET_CLASS(ClientboundCustomChatCompletionsPacket);
    DEFINE_PACKET_CLASS(ClientboundDeleteChatPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_PACKET_CLASS(ClientboundPlayerChatHeaderPacket);
#endif
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    DEFINE_PACKET_CLASS(ClientboundDisguisedChatPacket);
    DEFINE_PACKET_CLASS(ClientboundPlayerInfoRemovePacket);
    DEFINE_PACKET_CLASS(ClientboundPlayerInfoUpdatePacket);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    DEFINE_PACKET_CLASS(ClientboundUpdateEnabledFeaturesPacket);
#endif
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
    DEFINE_PACKET_CLASS(ClientboundBundlePacket);
    DEFINE_PACKET_CLASS(ClientboundChunksBiomesPacket);
    DEFINE_PACKET_CLASS(ClientboundDamageEventPacket);
    DEFINE_PACKET_CLASS(ClientboundHurtAnimationPacket);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    DEFINE_PACKET_CLASS(ClientboundChunkBatchFinishedPacket);
    DEFINE_PACKET_CLASS(ClientboundChunkBatchStartPacket);
    DEFINE_PACKET_CLASS(ClientboundPongResponsePacket);
    DEFINE_PACKET_CLASS(ClientboundStartConfigurationPacket);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    DEFINE_PACKET_CLASS(ClientboundResetScorePacket);
    DEFINE_PACKET_CLASS(ClientboundResourcePackPopPacket);
    DEFINE_PACKET_CLASS(ClientboundResourcePackPushPacket);
    DEFINE_PACKET_CLASS(ClientboundTickingStatePacket);
    DEFINE_PACKET_CLASS(ClientboundTickingStepPacket);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_PACKET_CLASS(ClientboundCookieRequestPacket);
    DEFINE_PACKET_CLASS(ClientboundDebugSamplePacket);
    DEFINE_PACKET_CLASS(ClientboundProjectilePowerPacket);
    DEFINE_PACKET_CLASS(ClientboundStoreCookiePacket);
    DEFINE_PACKET_CLASS(ClientboundTransferPacket);
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
    DEFINE_PACKET_CLASS(ClientboundCustomReportDetailsPacket);
    DEFINE_PACKET_CLASS(ClientboundServerLinksPacket);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    DEFINE_PACKET_CLASS(ClientboundMoveMinecartPacket);
    DEFINE_PACKET_CLASS(ClientboundEntityPositionSyncPacket);
    DEFINE_PACKET_CLASS(ClientboundPlayerRotationPacket);
    DEFINE_PACKET_CLASS(ClientboundRecipeBookAddPacket);
    DEFINE_PACKET_CLASS(ClientboundRecipeBookRemovePacket);
    DEFINE_PACKET_CLASS(ClientboundRecipeBookSettingsPacket);
    DEFINE_PACKET_CLASS(ClientboundSetCursorItemPacket);
    DEFINE_PACKET_CLASS(ClientboundSetHeldSlotPacket);
    DEFINE_PACKET_CLASS(ClientboundSetPlayerInventoryPacket);
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    DEFINE_PACKET_CLASS(ClientboundTestInstanceBlockStatusPacket);
#endif


    // Explicit instantiation for each serverbound packet class
    // Handshaking serverbound
    DEFINE_PACKET_CLASS(ServerboundClientIntentionPacket);

    // Login serverbound
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_PACKET_CLASS(ServerboundCookieResponseLoginPacket);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
    DEFINE_PACKET_CLASS(ServerboundCustomQueryPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundHelloPacket);
    DEFINE_PACKET_CLASS(ServerboundKeyPacket);
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    DEFINE_PACKET_CLASS(ServerboundCustomQueryAnswerPacket);
    DEFINE_PACKET_CLASS(ServerboundLoginAcknowledgedPacket);
#endif

    // Status serverbound
    DEFINE_PACKET_CLASS(ServerboundStatusRequestPacket);
    DEFINE_PACKET_CLASS(ServerboundPingRequestStatusPacket);

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    // Configuration serverbound
    DEFINE_PACKET_CLASS(ServerboundClientInformationConfigurationPacket);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_PACKET_CLASS(ServerboundCookieResponseConfigurationPacket);
    DEFINE_PACKET_CLASS(ServerboundSelectKnownPacksPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundCustomPayloadConfigurationPacket);
    DEFINE_PACKET_CLASS(ServerboundFinishConfigurationPacket);
    DEFINE_PACKET_CLASS(ServerboundKeepAliveConfigurationPacket);
    DEFINE_PACKET_CLASS(ServerboundPongConfigurationPacket);
    DEFINE_PACKET_CLASS(ServerboundResourcePackConfigurationPacket);
#endif

    // Play serverbound
    DEFINE_PACKET_CLASS(ServerboundSeenAdvancementsPacket);
    DEFINE_PACKET_CLASS(ServerboundSwingPacket);
    DEFINE_PACKET_CLASS(ServerboundChatPacket);
    DEFINE_PACKET_CLASS(ServerboundContainerClickPacket);
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ServerboundContainerButtonClickPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundClientInformationPacket);
    DEFINE_PACKET_CLASS(ServerboundClientCommandPacket);
    DEFINE_PACKET_CLASS(ServerboundContainerClosePacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_PACKET_CLASS(ServerboundContainerAckPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundPlaceRecipePacket);
    DEFINE_PACKET_CLASS(ServerboundSetCreativeModeSlotPacket);
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ServerboundEditBookPacket);
#endif
#if PROTOCOL_VERSION < 476 /* < 1.14 */
    DEFINE_PACKET_CLASS(ServerboundEnchantItemPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundPlayerCommandPacket);
#if PROTOCOL_VERSION > 711 /* > 1.15.2 */
    DEFINE_PACKET_CLASS(ServerboundJigsawGeneratePacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundSetCarriedItemPacket);
    DEFINE_PACKET_CLASS(ServerboundInteractPacket);
    DEFINE_PACKET_CLASS(ServerboundKeepAlivePacket);
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ServerboundLockDifficultyPacket);
#endif
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ServerboundRenameItemPacket);
#endif
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
    DEFINE_PACKET_CLASS(ServerboundPickItemFromBlockPacket);
    DEFINE_PACKET_CLASS(ServerboundPickItemFromEntityPacket);
#endif
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */ && PROTOCOL_VERSION < 769 /* < 1.21.4 */
    DEFINE_PACKET_CLASS(ServerboundPickItemPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundPlayerAbilitiesPacket);
    DEFINE_PACKET_CLASS(ServerboundUseItemOnPacket);
    DEFINE_PACKET_CLASS(ServerboundPlayerActionPacket);
    DEFINE_PACKET_CLASS(ServerboundMovePlayerPacketRot);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_PACKET_CLASS(ServerboundMovePlayerPacketStatusOnly);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_PACKET_CLASS(ServerboundMovePlayerPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundMovePlayerPacketPos);
    DEFINE_PACKET_CLASS(ServerboundMovePlayerPacketPosRot);
    DEFINE_PACKET_CLASS(ServerboundCustomPayloadPacket);
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ServerboundBlockEntityTagQueryPacket);
    DEFINE_PACKET_CLASS(ServerboundEntityTagQueryPacket);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
    DEFINE_PACKET_CLASS(ServerboundRecipeBookSeenRecipePacket);
    DEFINE_PACKET_CLASS(ServerboundRecipeBookChangeSettingsPacket);
#else
    DEFINE_PACKET_CLASS(ServerboundRecipeBookUpdatePacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundResourcePackPacket);
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ServerboundSelectTradePacket);
    DEFINE_PACKET_CLASS(ServerboundSetBeaconPacket);
#endif
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ServerboundChangeDifficultyPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundTeleportToEntityPacket);
    DEFINE_PACKET_CLASS(ServerboundPaddleBoatPacket);
    DEFINE_PACKET_CLASS(ServerboundPlayerInputPacket);
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
    DEFINE_PACKET_CLASS(ServerboundPlayerLoadedPacket);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_PACKET_CLASS(ServerboundPongPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundCommandSuggestionPacket);
    DEFINE_PACKET_CLASS(ServerboundAcceptTeleportationPacket);
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ServerboundSetCommandBlockPacket);
    DEFINE_PACKET_CLASS(ServerboundSetCommandMinecartPacket);
#endif
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
    DEFINE_PACKET_CLASS(ServerboundSetJigsawBlockPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundSignUpdatePacket);
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_PACKET_CLASS(ServerboundSetStructureBlockPacket);
#endif
    DEFINE_PACKET_CLASS(ServerboundUseItemPacket);
    DEFINE_PACKET_CLASS(ServerboundMoveVehiclePacket);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_PACKET_CLASS(ServerboundChatCommandPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_PACKET_CLASS(ServerboundChatPreviewPacket);
#endif
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    DEFINE_PACKET_CLASS(ServerboundChatAckPacket);
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    DEFINE_PACKET_CLASS(ServerboundChatSessionUpdatePacket);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    DEFINE_PACKET_CLASS(ServerboundChunkBatchReceivedPacket);
    DEFINE_PACKET_CLASS(ServerboundConfigurationAcknowledgedPacket);
    DEFINE_PACKET_CLASS(ServerboundPingRequestPacket);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    DEFINE_PACKET_CLASS(ServerboundContainerSlotStateChangedPacket);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_PACKET_CLASS(ServerboundChatCommandSignedPacket);
    DEFINE_PACKET_CLASS(ServerboundCookieResponsePacket);
    DEFINE_PACKET_CLASS(ServerboundDebugSampleSubscriptionPacket);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    DEFINE_PACKET_CLASS(ServerboundClientTickEndPacket);
    DEFINE_PACKET_CLASS(ServerboundSelectBundleItemPacket);
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    DEFINE_PACKET_CLASS(ServerboundSetTestBlockPacket);
    DEFINE_PACKET_CLASS(ServerboundTestInstanceBlockActionPacket);
#endif
}
