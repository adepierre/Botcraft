#include "protocolCraft/AllClientboundMessages.hpp"
#include "protocolCraft/AllServerboundMessages.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Handler.hpp"

namespace ProtocolCraft
{
    template<typename TDerived>
    int BaseMessage<TDerived>::GetId() const
    {
        if constexpr (Internal::tuple_contains_type<TDerived, AllClientboundPlayMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllClientboundPlayMessages>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundPlayMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundPlayMessages>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllClientboundStatusMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllClientboundStatusMessages>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundStatusMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundStatusMessages>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllClientboundLoginMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllClientboundLoginMessages>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundLoginMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundLoginMessages>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundHandshakingMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundHandshakingMessages>;
        }
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        else if constexpr (Internal::tuple_contains_type<TDerived, AllServerboundConfigurationMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllServerboundConfigurationMessages>;
        }
        else if constexpr (Internal::tuple_contains_type<TDerived, AllClientboundConfigurationMessages>)
        {
            return Internal::get_tuple_index<TDerived, AllClientboundConfigurationMessages>;
        }
#endif
        else
        {
            static_assert(Internal::dependant_false<TDerived>, "Trying to define a packet which is not in protocol tuples");
        }
    }

    template <typename TDerived>
    void BaseMessage<TDerived>::DispatchImpl(Handler* handler)
    {
        handler->Handle(static_cast<TDerived&>(*this));
    }

    // Explicit instantiation for each clientbound message class

    // Login clientbound
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_MESSAGE_CLASS(ClientboundCookieRequestLoginPacket);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ClientboundCustomQueryPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundLoginDisconnectPacket);
    DEFINE_MESSAGE_CLASS(ClientboundHelloPacket);
    DEFINE_MESSAGE_CLASS(ClientboundGameProfilePacket);
    DEFINE_MESSAGE_CLASS(ClientboundLoginCompressionPacket);

    // Status clientbound
    DEFINE_MESSAGE_CLASS(ClientboundStatusResponsePacket);
    DEFINE_MESSAGE_CLASS(ClientboundPongResponseStatusPacket);

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    // Configuration clientbound
    DEFINE_IMPLEMENTED_MESSAGE_CLASS(ClientboundCustomPayloadConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundDisconnectConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundFinishConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundKeepAliveConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPingConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundRegistryDataPacket);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    DEFINE_MESSAGE_CLASS(ClientboundResourcePackConfigurationPacket);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    DEFINE_MESSAGE_CLASS(ClientboundResourcePackPopConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundResourcePackPushConfigurationPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundUpdateEnabledFeaturesPacket);
    DEFINE_MESSAGE_CLASS(ClientboundUpdateTagsConfigurationPacket);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_MESSAGE_CLASS(ClientboundCookieRequestConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundResetChatPacket);
    DEFINE_MESSAGE_CLASS(ClientboundStoreCookieConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSelectKnownPacksPacket);
    DEFINE_MESSAGE_CLASS(ClientboundTransferConfigurationPacket);
#endif
#if PROTOCOL_VERSION > 766 /* > 1.21 */
    DEFINE_MESSAGE_CLASS(ClientboundCustomReportDetailsConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ClientboundServerLinksConfigurationPacket);
#endif
#endif

    // Play clientbound
    DEFINE_MESSAGE_CLASS(ClientboundUpdateAdvancementsPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetEntityLinkPacket);
    DEFINE_MESSAGE_CLASS(ClientboundBlockEventPacket);
    DEFINE_MESSAGE_CLASS(ClientboundBlockDestructionPacket);
    DEFINE_MESSAGE_CLASS(ClientboundBlockUpdatePacket);
    DEFINE_MESSAGE_CLASS(ClientboundBossEventPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetCameraPacket);
    DEFINE_MESSAGE_CLASS(ClientboundContainerClosePacket);
    DEFINE_MESSAGE_CLASS(ClientboundTakeItemEntityPacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_MESSAGE_CLASS(ClientboundPlayerCombatPacket);
#endif
#if PROTOCOL_VERSION == 755 /* 1.17 */
    DEFINE_MESSAGE_CLASS(ClientboundRemoveEntityPacket);
#else
    DEFINE_MESSAGE_CLASS(ClientboundRemoveEntitiesPacket);
#endif
#if PROTOCOL_VERSION > 345 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ClientboundCommandsPacket);
#endif
#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ClientboundUpdateRecipesPacket);
#endif
#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ClientboundPlayerLookAtPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundChangeDifficultyPacket);
    DEFINE_MESSAGE_CLASS(ClientboundMapItemDataPacket);
    DEFINE_SERIALIZED_MESSAGE_CLASS(ClientboundSectionBlocksUpdatePacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_MESSAGE_CLASS(ClientboundContainerAckPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundGameEventPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPlaceGhostRecipePacket);
    DEFINE_MESSAGE_CLASS(ClientboundDisconnectPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetDisplayObjectivePacket);
    DEFINE_MESSAGE_CLASS(ClientboundForgetLevelChunkPacket);
    DEFINE_MESSAGE_CLASS(ClientboundKeepAlivePacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_MESSAGE_CLASS(ClientboundCustomSoundPacket);
#endif
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ClientboundTagQueryPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundOpenSignEditorPacket);
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ClientboundHorseScreenOpenPacket);
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ClientboundOpenBookPacket);
#endif
#if PROTOCOL_VERSION < 757 /* < 1.18 */
    DEFINE_MESSAGE_CLASS(ClientboundLevelChunkPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundLoginPacket);
    DEFINE_MESSAGE_CLASS(ClientboundLevelEventPacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_MESSAGE_CLASS(ClientboundMoveEntityPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundAnimatePacket);
    DEFINE_SERIALIZED_MESSAGE_CLASS(ClientboundSetEquipmentPacket);
    DEFINE_MESSAGE_CLASS(ClientboundUpdateMobEffectPacket);
    DEFINE_MESSAGE_CLASS(ClientboundRotateHeadPacket);
    DEFINE_MESSAGE_CLASS(ClientboundMoveEntityPacketPos);
    DEFINE_MESSAGE_CLASS(ClientboundMoveEntityPacketPosRot);
    DEFINE_MESSAGE_CLASS(ClientboundMoveEntityPacketRot);
    DEFINE_MESSAGE_CLASS(ClientboundSetEntityDataPacket);
    DEFINE_MESSAGE_CLASS(ClientboundUpdateAttributesPacket);
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ClientboundSoundEntityPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundEntityEventPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetEntityMotionPacket);
    DEFINE_SERIALIZED_MESSAGE_CLASS(ClientboundExplodePacket);
    DEFINE_SERIALIZED_MESSAGE_CLASS(ClientboundLevelParticlesPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPlayerPositionPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetHealthPacket);
    DEFINE_MESSAGE_CLASS(ClientboundTeleportEntityPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPlayerAbilitiesPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetTimePacket);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_MESSAGE_CLASS(ClientboundChatPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundRespawnPacket);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    DEFINE_SERIALIZED_MESSAGE_CLASS(ClientboundLightUpdatePacket);
#endif
#if PROTOCOL_VERSION > 493 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_MESSAGE_CLASS(ClientboundBlockBreakAckPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundBlockEntityDataPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_IMPLEMENTED_MESSAGE_CLASS(ClientboundPlayerInfoPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundTabListPacket);
    DEFINE_IMPLEMENTED_MESSAGE_CLASS(ClientboundCustomPayloadPacket);
    DEFINE_MESSAGE_CLASS(ClientboundRemoveMobEffectPacket);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    DEFINE_MESSAGE_CLASS(ClientboundResourcePackPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundSetObjectivePacket);
    DEFINE_MESSAGE_CLASS(ClientboundSelectAdvancementsTabPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetExperiencePacket);
    DEFINE_MESSAGE_CLASS(ClientboundContainerSetSlotPacket);
    DEFINE_MESSAGE_CLASS(ClientboundCooldownPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetPassengersPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSoundPacket);
    DEFINE_MESSAGE_CLASS(ClientboundAddExperienceOrbPacket);
#if PROTOCOL_VERSION < 721 /* < 1.16 */
    DEFINE_MESSAGE_CLASS(ClientboundAddGlobalEntityPacket);
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_MESSAGE_CLASS(ClientboundAddMobPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundAddEntityPacket);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_MESSAGE_CLASS(ClientboundAddPaintingPacket);
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    DEFINE_MESSAGE_CLASS(ClientboundAddPlayerPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundSetDefaultSpawnPositionPacket);
    DEFINE_CUSTOM_SERIALIZED_MESSAGE_CLASS(ClientboundAwardStatsPacket);
#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ClientboundStopSoundPacket);
#endif
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ClientboundUpdateTagsPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundCommandSuggestionsPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetPlayerTeamPacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_MESSAGE_CLASS(ClientboundSetTitlesPacket);
#endif
#if PROTOCOL_VERSION < 461 /* < 1.14 */
    DEFINE_MESSAGE_CLASS(ClientboundUseBedPacket);
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ClientboundMerchantOffersPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundRecipePacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetScorePacket);
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ClientboundSetChunkCacheCenterPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetChunkCacheRadiusPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundMoveVehiclePacket);
    DEFINE_MESSAGE_CLASS(ClientboundContainerSetContentPacket);
    DEFINE_MESSAGE_CLASS(ClientboundContainerSetDataPacket);
    DEFINE_MESSAGE_CLASS(ClientboundOpenScreenPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetCarriedItemPacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_MESSAGE_CLASS(ClientboundSetBorderPacket);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_MESSAGE_CLASS(ClientboundAddVibrationSignalPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundClearTitlesPacket);
    DEFINE_MESSAGE_CLASS(ClientboundInitializeBorderPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPingPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPlayerCombatEndPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPlayerCombatEnterPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPlayerCombatKillPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetActionBarTextPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetBorderCenterPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetBorderLerpSizePacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetBorderSizePacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetBorderWarningDelayPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetBorderWarningDistancePacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetSubtitleTextPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetTitleTextPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetTitlesAnimationPacket);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    DEFINE_MESSAGE_CLASS(ClientboundLevelChunkWithLightPacket);
    DEFINE_MESSAGE_CLASS(ClientboundSetSimulationDistancePacket);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_MESSAGE_CLASS(ClientboundBlockChangedAckPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_MESSAGE_CLASS(ClientboundChatPreviewPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundPlayerChatPacket);
    DEFINE_MESSAGE_CLASS(ClientboundServerDataPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_MESSAGE_CLASS(ClientboundSetDisplayChatPreviewPacket);
#endif
    DEFINE_MESSAGE_CLASS(ClientboundSystemChatPacket);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    DEFINE_MESSAGE_CLASS(ClientboundCustomChatCompletionsPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_MESSAGE_CLASS(ClientboundDeleteChatPacket);
#else
    DEFINE_IMPLEMENTED_MESSAGE_CLASS(ClientboundDeleteChatPacket);
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_MESSAGE_CLASS(ClientboundPlayerChatHeaderPacket);
#endif
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    DEFINE_MESSAGE_CLASS(ClientboundDisguisedChatPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPlayerInfoRemovePacket);
    DEFINE_IMPLEMENTED_MESSAGE_CLASS(ClientboundPlayerInfoUpdatePacket);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    DEFINE_MESSAGE_CLASS(ClientboundUpdateEnabledFeaturesPacket);
#endif
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
    DEFINE_MESSAGE_CLASS(ClientboundBundlePacket);
    DEFINE_MESSAGE_CLASS(ClientboundChunksBiomesPacket);
    DEFINE_MESSAGE_CLASS(ClientboundDamageEventPacket);
    DEFINE_MESSAGE_CLASS(ClientboundHurtAnimationPacket);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    DEFINE_MESSAGE_CLASS(ClientboundChunkBatchFinishedPacket);
    DEFINE_MESSAGE_CLASS(ClientboundChunkBatchStartPacket);
    DEFINE_MESSAGE_CLASS(ClientboundPongResponsePacket);
    DEFINE_MESSAGE_CLASS(ClientboundStartConfigurationPacket);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    DEFINE_MESSAGE_CLASS(ClientboundResetScorePacket);
    DEFINE_MESSAGE_CLASS(ClientboundResourcePackPopPacket);
    DEFINE_MESSAGE_CLASS(ClientboundResourcePackPushPacket);
    DEFINE_MESSAGE_CLASS(ClientboundTickingStatePacket);
    DEFINE_MESSAGE_CLASS(ClientboundTickingStepPacket);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_MESSAGE_CLASS(ClientboundCookieRequestPacket);
    DEFINE_MESSAGE_CLASS(ClientboundDebugSamplePacket);
    DEFINE_MESSAGE_CLASS(ClientboundProjectilePowerPacket);
    DEFINE_MESSAGE_CLASS(ClientboundStoreCookiePacket);
    DEFINE_MESSAGE_CLASS(ClientboundTransferPacket);
#endif
#if PROTOCOL_VERSION > 766 /* > 1.21 */
    DEFINE_MESSAGE_CLASS(ClientboundCustomReportDetailsPacket);
    DEFINE_MESSAGE_CLASS(ClientboundServerLinksPacket);
#endif


    // Explicit instantiation for each serverbound message class
    // Handshaking serverbound
    DEFINE_MESSAGE_CLASS(ServerboundClientIntentionPacket);

    // Login serverbound
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_MESSAGE_CLASS(ServerboundCookieResponseLoginPacket);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
    DEFINE_MESSAGE_CLASS(ServerboundCustomQueryPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundHelloPacket);
    DEFINE_MESSAGE_CLASS(ServerboundKeyPacket);
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    DEFINE_MESSAGE_CLASS(ServerboundCustomQueryAnswerPacket);
    DEFINE_MESSAGE_CLASS(ServerboundLoginAcknowledgedPacket);
#endif

    // Status serverbound
    DEFINE_MESSAGE_CLASS(ServerboundStatusRequestPacket);
    DEFINE_MESSAGE_CLASS(ServerboundPingRequestStatusPacket);

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    // Configuration serverbound
    DEFINE_MESSAGE_CLASS(ServerboundClientInformationConfigurationPacket);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_MESSAGE_CLASS(ServerboundCookieResponseConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ServerboundSelectKnownPacksPacket);
#endif
    DEFINE_IMPLEMENTED_MESSAGE_CLASS(ServerboundCustomPayloadConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ServerboundFinishConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ServerboundKeepAliveConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ServerboundPongConfigurationPacket);
    DEFINE_MESSAGE_CLASS(ServerboundResourcePackConfigurationPacket);
#endif

    // Play serverbound
    DEFINE_MESSAGE_CLASS(ServerboundSeenAdvancementsPacket);
    DEFINE_MESSAGE_CLASS(ServerboundSwingPacket);
    DEFINE_MESSAGE_CLASS(ServerboundChatPacket);
    DEFINE_MESSAGE_CLASS(ServerboundContainerClickPacket);
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ServerboundContainerButtonClickPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundClientInformationPacket);
    DEFINE_MESSAGE_CLASS(ServerboundClientCommandPacket);
    DEFINE_MESSAGE_CLASS(ServerboundContainerClosePacket);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_MESSAGE_CLASS(ServerboundContainerAckPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundPlaceRecipePacket);
    DEFINE_MESSAGE_CLASS(ServerboundSetCreativeModeSlotPacket);
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ServerboundEditBookPacket);
#endif
#if PROTOCOL_VERSION < 476 /* < 1.14 */
    DEFINE_MESSAGE_CLASS(ServerboundEnchantItemPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundPlayerCommandPacket);
#if PROTOCOL_VERSION > 711 /* > 1.15.2 */
    DEFINE_MESSAGE_CLASS(ServerboundJigsawGeneratePacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundSetCarriedItemPacket);
    DEFINE_MESSAGE_CLASS(ServerboundInteractPacket);
    DEFINE_MESSAGE_CLASS(ServerboundKeepAlivePacket);
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ServerboundLockDifficultyPacket);
#endif
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ServerboundRenameItemPacket);
    DEFINE_MESSAGE_CLASS(ServerboundPickItemPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundPlayerAbilitiesPacket);
    DEFINE_MESSAGE_CLASS(ServerboundUseItemOnPacket);
    DEFINE_MESSAGE_CLASS(ServerboundPlayerActionPacket);
    DEFINE_MESSAGE_CLASS(ServerboundMovePlayerPacketRot);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_MESSAGE_CLASS(ServerboundMovePlayerPacketStatusOnly);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    DEFINE_MESSAGE_CLASS(ServerboundMovePlayerPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundMovePlayerPacketPos);
    DEFINE_MESSAGE_CLASS(ServerboundMovePlayerPacketPosRot);
    DEFINE_IMPLEMENTED_MESSAGE_CLASS(ServerboundCustomPayloadPacket);
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ServerboundBlockEntityTagQueryPacket);
    DEFINE_MESSAGE_CLASS(ServerboundEntityTagQueryPacket);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
    DEFINE_MESSAGE_CLASS(ServerboundRecipeBookSeenRecipePacket);
    DEFINE_MESSAGE_CLASS(ServerboundRecipeBookChangeSettingsPacket);
#else
    DEFINE_MESSAGE_CLASS(ServerboundRecipeBookUpdatePacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundResourcePackPacket);
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ServerboundSelectTradePacket);
    DEFINE_MESSAGE_CLASS(ServerboundSetBeaconPacket);
#endif
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ServerboundChangeDifficultyPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundTeleportToEntityPacket);
    DEFINE_MESSAGE_CLASS(ServerboundPaddleBoatPacket);
    DEFINE_MESSAGE_CLASS(ServerboundPlayerInputPacket);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_MESSAGE_CLASS(ServerboundPongPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundCommandSuggestionPacket);
    DEFINE_MESSAGE_CLASS(ServerboundAcceptTeleportationPacket);
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ServerboundSetCommandBlockPacket);
    DEFINE_MESSAGE_CLASS(ServerboundSetCommandMinecartPacket);
#endif
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
    DEFINE_MESSAGE_CLASS(ServerboundSetJigsawBlockPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundSignUpdatePacket);
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
    DEFINE_MESSAGE_CLASS(ServerboundSetStructureBlockPacket);
#endif
    DEFINE_MESSAGE_CLASS(ServerboundUseItemPacket);
    DEFINE_MESSAGE_CLASS(ServerboundMoveVehiclePacket);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_MESSAGE_CLASS(ServerboundChatCommandPacket);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_MESSAGE_CLASS(ServerboundChatPreviewPacket);
#endif
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    DEFINE_MESSAGE_CLASS(ServerboundChatAckPacket);
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    DEFINE_MESSAGE_CLASS(ServerboundChatSessionUpdatePacket);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    DEFINE_MESSAGE_CLASS(ServerboundChunkBatchReceivedPacket);
    DEFINE_MESSAGE_CLASS(ServerboundConfigurationAcknowledgedPacket);
    DEFINE_MESSAGE_CLASS(ServerboundPingRequestPacket);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    DEFINE_MESSAGE_CLASS(ServerboundContainerSlotStateChangedPacket);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_MESSAGE_CLASS(ServerboundChatCommandSignedPacket);
    DEFINE_MESSAGE_CLASS(ServerboundCookieResponsePacket);
    DEFINE_MESSAGE_CLASS(ServerboundDebugSampleSubscriptionPacket);
#endif
}
