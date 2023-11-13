#pragma once

#include <tuple>

#include "protocolCraft/Utilities/TupleCat.hpp"

// Handshaking serverbound
#include "protocolCraft/Messages/Handshaking/Serverbound/ServerboundClientIntentionPacket.hpp"


// Login serverbound
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */ 
#include "protocolCraft/Messages/Login/Serverbound/ServerboundCustomQueryPacket.hpp"
#endif
#include "protocolCraft/Messages/Login/Serverbound/ServerboundHelloPacket.hpp"
#include "protocolCraft/Messages/Login/Serverbound/ServerboundKeyPacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Login/Serverbound/ServerboundCustomQueryAnswerPacket.hpp"
#include "protocolCraft/Messages/Login/Serverbound/ServerboundLoginAcknowledgedPacket.hpp"
#endif

// Status Serverbound
#include "protocolCraft/Messages/Status/Serverbound/ServerboundPingRequestPacket.hpp"
#include "protocolCraft/Messages/Status/Serverbound/ServerboundStatusRequestPacket.hpp"

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
// Configuration Serverbound
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundClientInformationPacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundCustomPayloadPacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundFinishConfigurationPacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundKeepAlivePacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundPongPacket.hpp"
#include "protocolCraft/Messages/Configuration/Serverbound/ServerboundResourcePackPacket.hpp"
#endif

// Play serverbound
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientCommandPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPosRot.hpp"
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundKeepAlivePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientInformationPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundAcceptTeleportationPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerActionPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCommandSuggestionPacket.hpp"
#if PROTOCOL_VERSION < 476 /* < 1.14 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEnchantItemPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerClickPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerClosePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCustomPayloadPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundInteractPacket.hpp"
#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPos.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketRot.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMoveVehiclePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPaddleBoatPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlaceRecipePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerAbilitiesPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerCommandPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerInputPacket.hpp"
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookSeenRecipePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookChangeSettingsPacket.hpp"
#else
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRecipeBookUpdatePacket.hpp"
#endif

#include "protocolCraft/Messages/Play/Serverbound/ServerboundResourcePackPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSeenAdvancementsPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCarriedItemPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCreativeModeSlotPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSignUpdatePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSwingPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundTeleportToEntityPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundUseItemOnPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundUseItemPacket.hpp"
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundBlockEntityTagQuery.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEntityTagQuery.hpp"
#endif
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEditBookPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPickItemPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRenameItemPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSelectTradePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetBeaconPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandBlockPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandMinecartPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetStructureBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChangeDifficultyPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundLockDifficultyPacket.hpp"
#endif
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerButtonClickPacket.hpp"
#endif
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetJigsawBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 711 /* > 1.15.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundJigsawGeneratePacket.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketStatusOnly.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPongPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatCommandPacket.hpp"
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatPreviewPacket.hpp"
#endif
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatAckPacket.hpp"
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatSessionUpdatePacket.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChunkBatchReceivedPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundConfigurationAcknowledgedPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPingRequestPacket.hpp"
#endif

namespace ProtocolCraft
{
    using AllServerboundLoginMessages = std::tuple<
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ServerboundCustomQueryAnswerPacket,
        ServerboundLoginAcknowledgedPacket,
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        ServerboundCustomQueryPacket,
#endif
        ServerboundHelloPacket,
        ServerboundKeyPacket
    >;

    using AllServerboundStatusMessages = std::tuple<
        ServerboundStatusRequestPacket,
        ServerboundPingRequestStatusPacket
    >;

    using AllServerboundHandshakeMessages = std::tuple<
        ServerboundClientIntentionPacket
    >;

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    using AllServerboundConfigurationMessages = std::tuple<
        ServerboundClientInformationConfigurationPacket,
        ServerboundCustomPayloadConfigurationPacket,
        ServerboundFinishConfigurationPacket,
        ServerboundKeepAliveConfigurationPacket,
        ServerboundPongConfigurationPacket,
        ServerboundResourcePackConfigurationPacket
    >;
#endif

    using AllServerboundPlayMessages = std::tuple<
        ServerboundSeenAdvancementsPacket,
        ServerboundSwingPacket,
        ServerboundChatPacket,
        ServerboundContainerClickPacket,
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        ServerboundContainerButtonClickPacket,
#endif
        ServerboundClientInformationPacket,
        ServerboundClientCommandPacket,
        ServerboundContainerClosePacket,
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ServerboundContainerAckPacket,
#endif
        ServerboundPlaceRecipePacket,
        ServerboundSetCreativeModeSlotPacket,
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
        ServerboundEditBookPacket,
#endif
#if PROTOCOL_VERSION < 476 /* < 1.14 */
        ServerboundEnchantItemPacket,
#endif
        ServerboundPlayerCommandPacket,
#if PROTOCOL_VERSION > 711 /* > 1.15.2 */
        ServerboundJigsawGeneratePacket,
#endif
        ServerboundSetCarriedItemPacket,
        ServerboundInteractPacket,
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
        ServerboundLockDifficultyPacket,
#endif
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
        ServerboundRenameItemPacket,
        ServerboundPickItemPacket,
#endif
        ServerboundPlayerAbilitiesPacket,
        ServerboundUseItemOnPacket,
        ServerboundPlayerActionPacket,
        ServerboundMovePlayerPacketRot,
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        ServerboundMovePlayerPacket,
#endif
        ServerboundMovePlayerPacketPos,
        ServerboundMovePlayerPacketPosRot,
        ServerboundCustomPayloadPacket,
#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
        ServerboundBlockEntityTagQuery,
        ServerboundEntityTagQuery,
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        ServerboundRecipeBookSeenRecipePacket,
        ServerboundRecipeBookChangeSettingsPacket,
#else
        ServerboundRecipeBookUpdatePacket,
#endif
        ServerboundResourcePackPacket,
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
        ServerboundSelectTradePacket,
        ServerboundSetBeaconPacket,
#endif
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
        ServerboundChangeDifficultyPacket,
#endif
        ServerboundTeleportToEntityPacket,
        ServerboundPaddleBoatPacket,
        ServerboundPlayerInputPacket,
        ServerboundCommandSuggestionPacket,
        ServerboundAcceptTeleportationPacket,
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
        ServerboundSetCommandBlockPacket,
        ServerboundSetCommandMinecartPacket,
#endif
#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
        ServerboundSetJigsawBlockPacket,
#endif
        ServerboundSignUpdatePacket,
#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
        ServerboundSetStructureBlockPacket,
#endif
        ServerboundUseItemPacket,
        ServerboundMoveVehiclePacket,
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        ServerboundMovePlayerPacketStatusOnly,
        ServerboundPongPacket,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        ServerboundChatCommandPacket,
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ServerboundChatPreviewPacket,
#endif
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        ServerboundChatAckPacket,
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        ServerboundChatSessionUpdatePacket,
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        ServerboundChunkBatchReceivedPacket,
        ServerboundConfigurationAcknowledgedPacket,
        ServerboundPingRequestPacket,
#endif
        ServerboundKeepAlivePacket
    >;

    using AllServerboundMessages = Internal::tuple_cat_t <
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        AllServerboundConfigurationMessages,
#endif
        AllServerboundLoginMessages,
        AllServerboundStatusMessages,
        AllServerboundHandshakeMessages,
        AllServerboundPlayMessages
    >;
} //ProtocolCraft
