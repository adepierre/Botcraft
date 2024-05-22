#include "protocolCraft/BaseMessage.ipp"
#include "protocolCraft/AllServerboundMessages.hpp"
#include "protocolCraft/Utilities/PrivateTemplates.hpp"

namespace ProtocolCraft
{
    // Explicit instantiation for each serverbound message class
    // Handshaking serverbound
    template class BaseMessage<ServerboundClientIntentionPacket>;


    // Login serverbound
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    template class BaseMessage<ServerboundCookieResponseLoginPacket>;
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
    template class BaseMessage<ServerboundCustomQueryPacket>;
#endif
    template class BaseMessage<ServerboundHelloPacket>;
    template class BaseMessage<ServerboundKeyPacket>;
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    template class BaseMessage<ServerboundCustomQueryAnswerPacket>;
    template class BaseMessage<ServerboundLoginAcknowledgedPacket>;
#endif

    // Status serverbound
    template class BaseMessage<ServerboundStatusRequestPacket>;
    template class BaseMessage<ServerboundPingRequestStatusPacket>;

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    // Configuration serverbound
    template class BaseMessage<ServerboundClientInformationConfigurationPacket>;
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    template class BaseMessage<ServerboundCookieResponseConfigurationPacket>;
    template class BaseMessage<ServerboundSelectKnownPacksPacket>;
#endif
    template class BaseMessage<ServerboundCustomPayloadConfigurationPacket>;
    template class BaseMessage<ServerboundFinishConfigurationPacket>;
    template class BaseMessage<ServerboundKeepAliveConfigurationPacket>;
    template class BaseMessage<ServerboundPongConfigurationPacket>;
    template class BaseMessage<ServerboundResourcePackConfigurationPacket>;
#endif

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
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    template class BaseMessage<ServerboundMovePlayerPacketStatusOnly>;
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    template class BaseMessage<ServerboundMovePlayerPacket>;
#endif
    template class BaseMessage<ServerboundMovePlayerPacketPos>;
    template class BaseMessage<ServerboundMovePlayerPacketPosRot>;
    template class BaseMessage<ServerboundCustomPayloadPacket>;
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
    template class BaseMessage<ServerboundBlockEntityTagQueryPacket>;
    template class BaseMessage<ServerboundEntityTagQueryPacket>;
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
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
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
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    template class BaseMessage<ServerboundChatSessionUpdatePacket>;
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    template class BaseMessage<ServerboundChunkBatchReceivedPacket>;
    template class BaseMessage<ServerboundConfigurationAcknowledgedPacket>;
    template class BaseMessage<ServerboundPingRequestPacket>;
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    template class BaseMessage<ServerboundContainerSlotStateChangedPacket>;
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    template class BaseMessage<ServerboundChatCommandSignedPacket>;
    template class BaseMessage<ServerboundCookieResponsePacket>;
    template class BaseMessage<ServerboundDebugSampleSubscriptionPacket>;
#endif
}
