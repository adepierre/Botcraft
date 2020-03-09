#pragma once

#include <tuple>

// Handshaking serverbound
#include "protocolCraft/Messages/Handshaking/Serverbound/Handshake.hpp"


// Login serverbound
#include "protocolCraft/Messages/Login/Serverbound/LoginStart.hpp"
#include "protocolCraft/Messages/Login/Serverbound/EncryptionResponse.hpp"

// Login clientbound
#include "protocolCraft/Messages/Login/Clientbound/DisconnectLogin.hpp"
#include "protocolCraft/Messages/Login/Clientbound/EncryptionRequest.hpp"
#include "protocolCraft/Messages/Login/Clientbound/LoginSuccess.hpp"
#include "protocolCraft/Messages/Login/Clientbound/SetCompression.hpp"


// Play serverbound
#include "protocolCraft/Messages/Play/Serverbound/ChatMessageServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ClientStatus.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerPositionAndLookServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ConfirmTransactionServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/KeepAliveServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ClientSettings.hpp"
#include "protocolCraft/Messages/Play/Serverbound/TeleportConfirm.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerDigging.hpp"

// Play clientbound
#include "protocolCraft/Messages/Play/Clientbound/BlockChange.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ChatMessageClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ServerDifficulty.hpp"
#include "protocolCraft/Messages/Play/Clientbound/MultiBlockChange.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ConfirmTransactionClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/DisconnectPlay.hpp"
#include "protocolCraft/Messages/Play/Clientbound/UnloadChunk.hpp"
#include "protocolCraft/Messages/Play/Clientbound/KeepAliveClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ChunkData.hpp"
#include "protocolCraft/Messages/Play/Clientbound/JoinGame.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Entity.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityRelativeMove.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityLookAndRelativeMove.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityLook.hpp"
#include "protocolCraft/Messages/Play/Clientbound/PlayerPositionAndLookClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/UpdateHealth.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityTeleport.hpp"
#include "protocolCraft/Messages/Play/Clientbound/PlayerAbilitiesClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/TimeUpdate.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Respawn.hpp"
#if PROTOCOL_VERSION > 404
#include "protocolCraft/Messages/Play/Clientbound/UpdateLight.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/UpdateBlockEntity.hpp"
#include "protocolCraft/Messages/Play/Clientbound/PlayerInfo.hpp"
#if PROTOCOL_VERSION > 493
#include "protocolCraft/Messages/Play/Clientbound/AcknowledgePlayerDigging.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/SetSlot.hpp"
#include "protocolCraft/Messages/Play/Clientbound/WindowItems.hpp"
#include "protocolCraft/Messages/Play/Clientbound/OpenWindow.hpp"
#include "protocolCraft/Messages/Play/Clientbound/HeldItemChangeClientbound.hpp"

namespace ProtocolCraft
{
    using AllMessages = std::tuple <
        // Handshaking serverbound
        Handshake,


        // Login serverbound
        LoginStart,
        EncryptionResponse,

        // Login clientbound
        DisconnectLogin,
        EncryptionRequest,
        LoginSuccess,
        SetCompression,


        // Play serverbound
        ChatMessageServerbound,
        ClientStatus,
        PlayerPositionAndLookServerbound,
        ConfirmTransactionServerbound,
        KeepAliveServerbound,
        ClientSettings,
        TeleportConfirm,
        PlayerDigging,

        // Play clientbound
        BlockChange,
        ServerDifficulty,
        MultiBlockChange,
        ConfirmTransactionClientbound,
        DisconnectPlay,
        UnloadChunk,
        KeepAliveClientbound,
        ChunkData,
        JoinGame,
        Entity,
        EntityRelativeMove,
        EntityLookAndRelativeMove,
        EntityLook,
        PlayerPositionAndLookClientbound,
        UpdateHealth,
        EntityTeleport,
        PlayerAbilitiesClientbound,
        TimeUpdate,
        ChatMessageClientbound,
        Respawn
#if PROTOCOL_VERSION > 404
        ,UpdateLight
#endif
#if PROTOCOL_VERSION > 493
        ,AcknowledgePlayerDigging
#endif
        ,UpdateBlockEntity,
        PlayerInfo,
        SetSlot,
        WindowItems,
        OpenWindow,
        HeldItemChangeClientbound
    > ;
} //ProtocolCraft