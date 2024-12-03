#pragma once

#include "protocolCraft/Utilities/Templates.hpp"

// Configuration
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundClientInformationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundCookieResponsePacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundCustomPayloadPacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundFinishConfigurationPacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundKeepAlivePacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundPongPacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundResourcePackPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundSelectKnownPacksPacket.hpp"
#endif

// Handshaking
#include "protocolCraft/Messages/Handshaking/Serverbound/ServerboundClientIntentionPacket.hpp"

// Login
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Login/Serverbound/ServerboundCookieResponsePacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Messages/Login/Serverbound/ServerboundCustomQueryPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Login/Serverbound/ServerboundCustomQueryAnswerPacket.hpp"
#endif
#include "protocolCraft/Messages/Login/Serverbound/ServerboundHelloPacket.hpp"
#include "protocolCraft/Messages/Login/Serverbound/ServerboundKeyPacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Login/Serverbound/ServerboundLoginAcknowledgedPacket.hpp"
#endif

// Play
#include "protocolCraft/Messages/Play/Serverbound/ServerboundAcceptTeleportationPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundBlockEntityTagQueryPacket.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChangeDifficultyPacket.hpp"
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatAckPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatCommandPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatCommandSignedPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatPacket.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatPreviewPacket.hpp"
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatSessionUpdatePacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChunkBatchReceivedPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientCommandPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientInformationPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCommandSuggestionPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientTickEndPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundConfigurationAcknowledgedPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerAckPacket.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerButtonClickPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerClickPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerClosePacket.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerSlotStateChangedPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCookieResponsePacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCustomPayloadPacket.hpp"
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundDebugSampleSubscriptionPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEditBookPacket.hpp"
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEnchantItemPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEntityTagQueryPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundInteractPacket.hpp"
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundJigsawGeneratePacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundKeepAlivePacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundLockDifficultyPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPos.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPosRot.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketRot.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketStatusOnly.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMoveVehiclePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPaddleBoatPacket.hpp"
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPickItemFromBlockPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPickItemFromEntityPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 769 /* < 1.21.4 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPickItemPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPingRequestPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlaceRecipePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerAbilitiesPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerActionPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerCommandPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerInputPacket.hpp"
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerLoadedPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPongPacket.hpp"
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookChangeSettingsPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookSeenRecipePacket.hpp"
#endif
#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookUpdatePacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRenameItemPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundResourcePackPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSeenAdvancementsPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSelectBundleItemPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSelectTradePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetBeaconPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCarriedItemPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandBlockPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandMinecartPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCreativeModeSlotPacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetJigsawBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetStructureBlockPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSignUpdatePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSwingPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundTeleportToEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundUseItemOnPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundUseItemPacket.hpp"

// Status
#include "protocolCraft/Messages/Status/Serverbound/ServerboundPingRequestPacket.hpp"
#include "protocolCraft/Messages/Status/Serverbound/ServerboundStatusRequestPacket.hpp"


namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    using AllServerboundConfigurationMessages = std::tuple<
        ServerboundClientInformationConfigurationPacket,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ServerboundCookieResponseConfigurationPacket,
#endif
        ServerboundCustomPayloadConfigurationPacket,
        ServerboundFinishConfigurationPacket,
        ServerboundKeepAliveConfigurationPacket,
        ServerboundPongConfigurationPacket,
        ServerboundResourcePackConfigurationPacket
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ,
        ServerboundSelectKnownPacksPacket
#endif
    >;
#endif

    using AllServerboundHandshakingMessages = std::tuple<
        ServerboundClientIntentionPacket
    >;

    using AllServerboundLoginMessages = std::tuple<
        ServerboundHelloPacket,
        ServerboundKeyPacket
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        ,
        ServerboundCustomQueryPacket
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ,
        ServerboundCustomQueryAnswerPacket,
        ServerboundLoginAcknowledgedPacket
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ,
        ServerboundCookieResponseLoginPacket
#endif
    >;

    using AllServerboundPlayMessages = std::tuple<
        ServerboundAcceptTeleportationPacket,
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ServerboundBlockEntityTagQueryPacket,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ServerboundSelectBundleItemPacket,
#endif
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        ServerboundCommandSuggestionPacket,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ServerboundChangeDifficultyPacket,
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        ServerboundChatAckPacket,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        ServerboundChatCommandPacket,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ServerboundChatCommandSignedPacket,
#endif
        ServerboundChatPacket,
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ServerboundChatPreviewPacket,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ServerboundChatSessionUpdatePacket,
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ServerboundChunkBatchReceivedPacket,
#endif
        ServerboundClientCommandPacket,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ServerboundClientTickEndPacket,
#endif
        ServerboundClientInformationPacket,
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ServerboundCommandSuggestionPacket,
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ServerboundConfigurationAcknowledgedPacket,
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ServerboundContainerAckPacket,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ServerboundContainerButtonClickPacket,
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        ServerboundEnchantItemPacket,
#endif
        ServerboundContainerClickPacket,
        ServerboundContainerClosePacket,
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        ServerboundContainerSlotStateChangedPacket,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ServerboundCookieResponsePacket,
#endif
        ServerboundCustomPayloadPacket,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ServerboundDebugSampleSubscriptionPacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ServerboundEditBookPacket,
        ServerboundEntityTagQueryPacket,
#endif
        ServerboundInteractPacket,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        ServerboundJigsawGeneratePacket,
#endif
        ServerboundKeepAlivePacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ServerboundLockDifficultyPacket,
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        ServerboundMovePlayerPacket,
#endif
        ServerboundMovePlayerPacketPos,
        ServerboundMovePlayerPacketPosRot,
        ServerboundMovePlayerPacketRot,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 755 /* < 1.17 */
        ServerboundMovePlayerPacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ServerboundMovePlayerPacketStatusOnly,
#endif
        ServerboundMoveVehiclePacket,
        ServerboundPaddleBoatPacket,
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        ServerboundPickItemFromBlockPacket,
        ServerboundPickItemFromEntityPacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 769 /* < 1.21.4 */
        ServerboundPickItemPacket,
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ServerboundPingRequestPacket,
#endif
        ServerboundPlaceRecipePacket,
        ServerboundPlayerAbilitiesPacket,
        ServerboundPlayerActionPacket,
        ServerboundPlayerCommandPacket,
        ServerboundPlayerInputPacket,
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        ServerboundPlayerLoadedPacket,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ServerboundPongPacket,
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        ServerboundChatSessionUpdatePacket,
#endif
#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
        ServerboundRecipeBookUpdatePacket,
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        ServerboundRecipeBookChangeSettingsPacket,
        ServerboundRecipeBookSeenRecipePacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ServerboundRenameItemPacket,
#endif
        ServerboundResourcePackPacket,
        ServerboundSeenAdvancementsPacket,
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ServerboundSelectTradePacket,
        ServerboundSetBeaconPacket,
#endif
        ServerboundSetCarriedItemPacket,
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ServerboundSetCommandBlockPacket,
        ServerboundSetCommandMinecartPacket,
#endif
        ServerboundSetCreativeModeSlotPacket,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ServerboundSetJigsawBlockPacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ServerboundSetStructureBlockPacket,
#endif
        ServerboundSignUpdatePacket,
        ServerboundSwingPacket,
        ServerboundTeleportToEntityPacket,
        ServerboundUseItemOnPacket,
        ServerboundUseItemPacket
    >;

    using AllServerboundStatusMessages = std::tuple<
        ServerboundStatusRequestPacket,
        ServerboundPingRequestStatusPacket
    >;

    using AllServerboundMessages = Internal::tuple_cat_t<
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        AllServerboundConfigurationMessages,
#endif
        AllServerboundHandshakingMessages,
        AllServerboundLoginMessages,
        AllServerboundPlayMessages,
        AllServerboundStatusMessages
    >;
} //ProtocolCraft
