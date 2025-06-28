#pragma once

#include "protocolCraft/Utilities/Templates.hpp"

// Configuration
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundClientInformationPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundCookieResponsePacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundCustomPayloadPacket.hpp"
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundFinishConfigurationPacket.hpp"
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundKeepAlivePacket.hpp"
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundPongPacket.hpp"
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundResourcePackPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundSelectKnownPacksPacket.hpp"
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Packets/Configuration/Serverbound/ServerboundCustomClickActionPacket.hpp"
#endif

// Handshaking
#include "protocolCraft/Packets/Handshake/Serverbound/ServerboundClientIntentionPacket.hpp"

// Login
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Login/Serverbound/ServerboundCookieResponsePacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Packets/Login/Serverbound/ServerboundCustomQueryPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Login/Serverbound/ServerboundCustomQueryAnswerPacket.hpp"
#endif
#include "protocolCraft/Packets/Login/Serverbound/ServerboundHelloPacket.hpp"
#include "protocolCraft/Packets/Login/Serverbound/ServerboundKeyPacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Login/Serverbound/ServerboundLoginAcknowledgedPacket.hpp"
#endif

// Play
#include "protocolCraft/Packets/Game/Serverbound/ServerboundAcceptTeleportationPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundBlockEntityTagQueryPacket.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChangeDifficultyPacket.hpp"
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChangeGameModePacket.hpp"
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChatAckPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChatCommandPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChatCommandSignedPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChatPacket.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChatPreviewPacket.hpp"
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChatSessionUpdatePacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundChunkBatchReceivedPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundClientCommandPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundClientInformationPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundCommandSuggestionPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundClientTickEndPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundConfigurationAcknowledgedPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundContainerAckPacket.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundContainerButtonClickPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundContainerClickPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundContainerClosePacket.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundContainerSlotStateChangedPacket.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundCookieResponsePacket.hpp"
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundCustomClickActionPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundCustomPayloadPacket.hpp"
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundDebugSampleSubscriptionPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundEditBookPacket.hpp"
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundEnchantItemPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundEntityTagQueryPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundInteractPacket.hpp"
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundJigsawGeneratePacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundKeepAlivePacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundLockDifficultyPacket.hpp"
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacketPos.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacketPosRot.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacketRot.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundMovePlayerPacketStatusOnly.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundMoveVehiclePacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPaddleBoatPacket.hpp"
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPickItemFromBlockPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPickItemFromEntityPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 769 /* < 1.21.4 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPickItemPacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPingRequestPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPlaceRecipePacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPlayerAbilitiesPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPlayerActionPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPlayerCommandPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPlayerInputPacket.hpp"
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPlayerLoadedPacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundPongPacket.hpp"
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundRecipeBookChangeSettingsPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundRecipeBookSeenRecipePacket.hpp"
#endif
#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundRecipeBookUpdatePacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundRenameItemPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundResourcePackPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSeenAdvancementsPacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSelectBundleItemPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSelectTradePacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSetBeaconPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSetCarriedItemPacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSetCommandBlockPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSetCommandMinecartPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSetCreativeModeSlotPacket.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSetJigsawBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSetStructureBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSetTestBlockPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSignUpdatePacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundSwingPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundTeleportToEntityPacket.hpp"
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "protocolCraft/Packets/Game/Serverbound/ServerboundTestInstanceBlockActionPacket.hpp"
#endif
#include "protocolCraft/Packets/Game/Serverbound/ServerboundUseItemOnPacket.hpp"
#include "protocolCraft/Packets/Game/Serverbound/ServerboundUseItemPacket.hpp"

// Status
#include "protocolCraft/Packets/Status/Serverbound/ServerboundPingRequestPacket.hpp"
#include "protocolCraft/Packets/Status/Serverbound/ServerboundStatusRequestPacket.hpp"


namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    using AllServerboundConfigurationPackets = std::tuple<
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
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        ,
        ServerboundCustomClickActionConfigurationPacket
#endif
    >;
#endif

    using AllServerboundHandshakingPackets = std::tuple<
        ServerboundClientIntentionPacket
    >;

    using AllServerboundLoginPackets = std::tuple<
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

    using AllServerboundPlayPackets = std::tuple<
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
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        ServerboundChangeGameModePacket,
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
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        ServerboundSetTestBlockPacket,
#endif
        ServerboundSignUpdatePacket,
        ServerboundSwingPacket,
        ServerboundTeleportToEntityPacket,
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        ServerboundTestInstanceBlockActionPacket,
#endif
        ServerboundUseItemOnPacket,
        ServerboundUseItemPacket
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        ,
        ServerboundCustomClickActionPacket
#endif
    >;

    using AllServerboundStatusPackets = std::tuple<
        ServerboundStatusRequestPacket,
        ServerboundPingRequestStatusPacket
    >;

    using AllServerboundPackets = Internal::tuple_cat_t<
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        AllServerboundConfigurationPackets,
#endif
        AllServerboundHandshakingPackets,
        AllServerboundLoginPackets,
        AllServerboundPlayPackets,
        AllServerboundStatusPackets
    >;
} //ProtocolCraft
