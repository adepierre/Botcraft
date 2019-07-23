#pragma once

#include <tuple>

#include "botcraft/Version.hpp"

// Handshaking serverbound
#include "botcraft/Protocol/Messages/Handshaking/Serverbound/Handshake.hpp"


// Login serverbound
#include "botcraft/Protocol/Messages/Login/Serverbound/LoginStart.hpp"

// Login clientbound
#include "botcraft/Protocol/Messages/Login/Clientbound/DisconnectLogin.hpp"
#include "botcraft/Protocol/Messages/Login/Clientbound/EncryptionRequest.hpp"
#include "botcraft/Protocol/Messages/Login/Clientbound/LoginSuccess.hpp"
#include "botcraft/Protocol/Messages/Login/Clientbound/SetCompression.hpp"


// Play serverbound
#include "botcraft/Protocol/Messages/Play/Serverbound/ChatMessageServerbound.hpp"
#include "botcraft/Protocol/Messages/Play/Serverbound/ClientStatus.hpp"
#include "botcraft/Protocol/Messages/Play/Serverbound/PlayerPositionAndLookServerbound.hpp"
#include "botcraft/Protocol/Messages/Play/Serverbound/ConfirmTransactionServerbound.hpp"
#include "botcraft/Protocol/Messages/Play/Serverbound/KeepAliveServerbound.hpp"
#include "botcraft/Protocol/Messages/Play/Serverbound/ClientSettings.hpp"
#include "botcraft/Protocol/Messages/Play/Serverbound/TeleportConfirm.hpp"
#include "botcraft/Protocol/Messages/Play/Serverbound/PlayerDigging.hpp"

// Play clientbound
#include "botcraft/Protocol/Messages/Play/Clientbound/BlockChange.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/ChatMessageClientBound.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/ServerDifficulty.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/MultiBlockChange.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/ConfirmTransactionClientbound.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/DisconnectPlay.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/UnloadChunk.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/KeepAliveClientbound.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/ChunkData.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/JoinGame.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/Entity.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/EntityRelativeMove.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/EntityLookAndRelativeMove.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/EntityLook.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/PlayerPositionAndLookClientbound.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/UpdateHealth.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/EntityTeleport.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/PlayerAbilitiesClientbound.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/TimeUpdate.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/Respawn.hpp"
#if PROTOCOL_VERSION > 404
#include "botcraft/Protocol/Messages/Play/Clientbound/UpdateLight.hpp"
#endif
#include "botcraft/Protocol/Messages/Play/Clientbound/UpdateBlockEntity.hpp"
#include "botcraft/Protocol/Messages/Play/Clientbound/PlayerInfo.hpp"
#if PROTOCOL_VERSION > 493
#include "botcraft/Protocol/Messages/Play/Clientbound/AcknowledgePlayerDigging.hpp"
#endif

namespace Botcraft
{
    using AllMessages = std::tuple <
        // Handshaking serverbound
        Handshake,


        // Login serverbound
        LoginStart,

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
        PlayerInfo
    > ;
} //Botcraft