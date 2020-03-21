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
#include "protocolCraft/Messages/Play/Clientbound/SpawnObject.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SpawnExperienceOrb.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SpawnGlobalEntity.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SpawnMob.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SpawnPainting.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SpawnPlayer.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityAnimationClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Statistics.hpp"
#include "protocolCraft/Messages/Play/Clientbound/BlockBreakAnimation.hpp"
#include "protocolCraft/Messages/Play/Clientbound/BlockAction.hpp"
#include "protocolCraft/Messages/Play/Clientbound/BossBar.hpp"
#include "protocolCraft/Messages/Play/Clientbound/TabCompleteClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/CloseWindowClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/WindowProperty.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SetCooldown.hpp"
#include "protocolCraft/Messages/Play/Clientbound/PluginMessageClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/NamedSoundEffect.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityStatus.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Explosion.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ChangeGameState.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Effect.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Particle.hpp"
#include "protocolCraft/Messages/Play/Clientbound/MapData.hpp"
#include "protocolCraft/Messages/Play/Clientbound/VehicleMoveClientbound.hpp"
#include "protocolCraft/Messages/Play/Clientbound/OpenSignEditor.hpp"
#include "protocolCraft/Messages/Play/Clientbound/CraftRecipeResponse.hpp"
#include "protocolCraft/Messages/Play/Clientbound/CombatEvent.hpp"
#if PROTOCOL_VERSION < 461
#include "protocolCraft/Messages/Play/Clientbound/UseBed.hpp"
#endif
#include "protocolCraft/Messages/Play/Clientbound/UnlockRecipes.hpp"
#include "protocolCraft/Messages/Play/Clientbound/DestroyEntities.hpp"
#include "protocolCraft/Messages/Play/Clientbound/RemoveEntityEffect.hpp"
#include "protocolCraft/Messages/Play/Clientbound/RessourcePackSend.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityHeadLook.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SelectAdvancementTab.hpp"
#include "protocolCraft/Messages/Play/Clientbound/WorldBorder.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Camera.hpp"
#include "protocolCraft/Messages/Play/Clientbound/DisplayScoreboard.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityMetadata.hpp"
#include "protocolCraft/Messages/Play/Clientbound/AttachEntity.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityVelocity.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityEquipment.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SetExperience.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ScoreboardObjective.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SetPassengers.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Teams.hpp"

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
        AttachEntity,
        BlockAction,
        BlockBreakAnimation,
        BlockChange,
        BossBar,
        Camera,
        CloseWindowClientbound,
        CombatEvent,
        DestroyEntities,
        ServerDifficulty,
        MapData,
        MultiBlockChange,
        ConfirmTransactionClientbound,
        ChangeGameState,
        CraftRecipeResponse,
        DisconnectPlay,
        DisplayScoreboard,
        UnloadChunk,
        KeepAliveClientbound,
        NamedSoundEffect,
        OpenSignEditor,
        ChunkData,
        JoinGame,
        Effect,
        Entity,
        EntityAnimationClientbound,
        EntityEquipment,
        EntityHeadLook,
        EntityRelativeMove,
        EntityLookAndRelativeMove,
        EntityLook,
        EntityMetadata,
        EntityStatus,
        EntityVelocity,
        Explosion,
        Particle,
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
        PluginMessageClientbound,
        RemoveEntityEffect,
        RessourcePackSend,
        ScoreboardObjective,
        SelectAdvancementTab,
        SetExperience,
        SetSlot,
        SetCooldown,
        SetPassengers,
        SpawnExperienceOrb,
        SpawnGlobalEntity,
        SpawnMob,
        SpawnObject,
        SpawnPainting,
        SpawnPlayer,
        Statistics,
        TabCompleteClientbound,
        Teams,
#if PROTOCOL_VERSION < 461
        UseBed,
#endif
        UnlockRecipes,
        VehicleMoveClientbound,
        WindowItems,
        WindowProperty,
        OpenWindow,
        HeldItemChangeClientbound,
        WorldBorder
    > ;
} //ProtocolCraft