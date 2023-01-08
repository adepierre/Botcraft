#pragma once

#include <tuple>

#include "protocolCraft/Utilities/TupleCat.hpp"

// Handshaking serverbound
#include "protocolCraft/Messages/Handshaking/Serverbound/ServerboundClientIntentionPacket.hpp"


// Login serverbound
#if PROTOCOL_VERSION > 340
#include "protocolCraft/Messages/Login/Serverbound/ServerboundCustomQueryPacket.hpp"
#endif
#include "protocolCraft/Messages/Login/Serverbound/ServerboundHelloPacket.hpp"
#include "protocolCraft/Messages/Login/Serverbound/ServerboundKeyPacket.hpp"

//Status Serverbound
#include "protocolCraft/Messages/Status/Serverbound/ServerboundPingRequestPacket.hpp"
#include "protocolCraft/Messages/Status/Serverbound/ServerboundStatusRequestPacket.hpp"

// Play serverbound
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientCommandPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketPosRot.hpp"
#if PROTOCOL_VERSION < 755
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerAckPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundKeepAlivePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundClientInformationPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundAcceptTeleportationPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPlayerActionPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCommandSuggestionPacket.hpp"
#if PROTOCOL_VERSION < 476
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEnchantItemPacket.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerClickPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerClosePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundCustomPayloadPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundInteractPacket.hpp"
#if PROTOCOL_VERSION < 755
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
#if PROTOCOL_VERSION > 736
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
#if PROTOCOL_VERSION > 388
#include "protocolCraft/Messages/Play/Serverbound/ServerboundBlockEntityTagQuery.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEntityTagQuery.hpp"
#endif
#if PROTOCOL_VERSION > 385
#include "protocolCraft/Messages/Play/Serverbound/ServerboundEditBookPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPickItemPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundRenameItemPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSelectTradePacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetBeaconPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandBlockPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetCommandMinecartPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetStructureBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 463
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChangeDifficultyPacket.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundLockDifficultyPacket.hpp"
#endif
#if PROTOCOL_VERSION > 476
#include "protocolCraft/Messages/Play/Serverbound/ServerboundContainerButtonClickPacket.hpp"
#endif
#if PROTOCOL_VERSION > 471
#include "protocolCraft/Messages/Play/Serverbound/ServerboundSetJigsawBlockPacket.hpp"
#endif
#if PROTOCOL_VERSION > 711
#include "protocolCraft/Messages/Play/Serverbound/ServerboundJigsawGeneratePacket.hpp"
#endif
#if PROTOCOL_VERSION > 754
#include "protocolCraft/Messages/Play/Serverbound/ServerboundMovePlayerPacketStatusOnly.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ServerboundPongPacket.hpp"
#endif
#if PROTOCOL_VERSION > 758
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatCommandPacket.hpp"
#if PROTOCOL_VERSION < 761
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatPreviewPacket.hpp"
#endif
#endif
#if PROTOCOL_VERSION > 759
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatAckPacket.hpp"
#endif
#if PROTOCOL_VERSION > 760
#include "protocolCraft/Messages/Play/Serverbound/ServerboundChatSessionUpdatePacket.hpp"
#endif

namespace ProtocolCraft
{
    using AllServerboundLoginMessages = std::tuple<
#if PROTOCOL_VERSION > 340
        ServerboundCustomQueryPacket,
#endif
        ServerboundHelloPacket,
        ServerboundKeyPacket
    >;

    using AllServerboundStatusMessages = std::tuple<
        ServerboundStatusRequestPacket,
        ServerboundPingRequestPacket
    >;

    using AllServerboundHandshakeMessages = std::tuple<
        ServerboundClientIntentionPacket
    >;

    using AllServerboundPlayMessages = std::tuple<
        ServerboundSeenAdvancementsPacket,
        ServerboundSwingPacket,
        ServerboundChatPacket,
        ServerboundContainerClickPacket,
#if PROTOCOL_VERSION > 476
        ServerboundContainerButtonClickPacket,
#endif
        ServerboundClientInformationPacket,
        ServerboundClientCommandPacket,
        ServerboundContainerClosePacket,
#if PROTOCOL_VERSION < 755
        ServerboundContainerAckPacket,
#endif
        ServerboundPlaceRecipePacket,
        ServerboundSetCreativeModeSlotPacket,
#if PROTOCOL_VERSION > 385
        ServerboundEditBookPacket,
#endif
#if PROTOCOL_VERSION < 476
        ServerboundEnchantItemPacket,
#endif
        ServerboundPlayerCommandPacket,
#if PROTOCOL_VERSION > 711
        ServerboundJigsawGeneratePacket,
#endif
        ServerboundSetCarriedItemPacket,
        ServerboundInteractPacket,
#if PROTOCOL_VERSION > 463
        ServerboundLockDifficultyPacket,
#endif
#if PROTOCOL_VERSION > 385
        ServerboundRenameItemPacket,
        ServerboundPickItemPacket,
#endif
        ServerboundPlayerAbilitiesPacket,
        ServerboundUseItemOnPacket,
        ServerboundPlayerActionPacket,
        ServerboundMovePlayerPacketRot,
#if PROTOCOL_VERSION < 755
        ServerboundMovePlayerPacket,
#endif
        ServerboundMovePlayerPacketPos,
        ServerboundMovePlayerPacketPosRot,
        ServerboundCustomPayloadPacket,
#if PROTOCOL_VERSION > 388
        ServerboundBlockEntityTagQuery,
        ServerboundEntityTagQuery,
#endif
#if PROTOCOL_VERSION > 736
        ServerboundRecipeBookSeenRecipePacket,
        ServerboundRecipeBookChangeSettingsPacket,
#else
        ServerboundRecipeBookUpdatePacket,
#endif
        ServerboundResourcePackPacket,
#if PROTOCOL_VERSION > 385
        ServerboundSelectTradePacket,
        ServerboundSetBeaconPacket,
#endif
#if PROTOCOL_VERSION > 463
        ServerboundChangeDifficultyPacket,
#endif
        ServerboundTeleportToEntityPacket,
        ServerboundPaddleBoatPacket,
        ServerboundPlayerInputPacket,
        ServerboundCommandSuggestionPacket,
        ServerboundAcceptTeleportationPacket,
#if PROTOCOL_VERSION > 385
        ServerboundSetCommandBlockPacket,
        ServerboundSetCommandMinecartPacket,
#endif
#if PROTOCOL_VERSION > 471
        ServerboundSetJigsawBlockPacket,
#endif
        ServerboundSignUpdatePacket,
#if PROTOCOL_VERSION > 385
        ServerboundSetStructureBlockPacket,
#endif
        ServerboundUseItemPacket,
        ServerboundMoveVehiclePacket,
#if PROTOCOL_VERSION > 754
        ServerboundMovePlayerPacketStatusOnly,
        ServerboundPongPacket,
#endif
#if PROTOCOL_VERSION > 758
        ServerboundChatCommandPacket,
#if PROTOCOL_VERSION < 761
        ServerboundChatPreviewPacket,
#endif
#endif
#if PROTOCOL_VERSION > 759
        ServerboundChatAckPacket,
#endif
#if PROTOCOL_VERSION > 760
        ServerboundChatSessionUpdatePacket,
#endif
        ServerboundKeepAlivePacket
    >;

    using AllServerboundMessages = Internal::tuple_cat_t <
        AllServerboundLoginMessages,
        AllServerboundStatusMessages,
        AllServerboundHandshakeMessages,
        AllServerboundPlayMessages
    >;
} //ProtocolCraft
