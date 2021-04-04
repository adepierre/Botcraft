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

//Status Serverbound
#include "protocolCraft/Messages/Status/Serverbound/Ping.hpp"
#include "protocolCraft/Messages/Status/Serverbound/Request.hpp"

// Status Clientbound
#include "protocolCraft/Messages/Status/Clientbound/Pong.hpp"
#include "protocolCraft/Messages/Status/Clientbound/Response.hpp"

// Play serverbound
#include "protocolCraft/Messages/Play/Serverbound/ChatMessageServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ClientStatus.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerPositionAndLookServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ConfirmTransactionServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/KeepAliveServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/ClientSettings.hpp"
#include "protocolCraft/Messages/Play/Serverbound/TeleportConfirm.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerDigging.hpp"
#include "protocolCraft/Messages/Play/Serverbound/TabCompleteServerbound.hpp"
#if PROTOCOL_VERSION < 476
#include "protocolCraft/Messages/Play/Serverbound/EnchantItem.hpp"
#endif
#include "protocolCraft/Messages/Play/Serverbound/ClickWindow.hpp"
#include "protocolCraft/Messages/Play/Serverbound/CloseWindowServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PluginMessageServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/InteractEntity.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerMovement.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerPosition.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerLook.hpp"
#include "protocolCraft/Messages/Play/Serverbound/VehicleMoveServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/SteerBoat.hpp"
#include "protocolCraft/Messages/Play/Serverbound/CraftRecipeRequest.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerAbilitiesServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/EntityAction.hpp"
#include "protocolCraft/Messages/Play/Serverbound/SteerVehicle.hpp"
#if PROTOCOL_VERSION < 737
#include "protocolCraft/Messages/Play/Serverbound/RecipeBookData.hpp"
#else
#include "protocolCraft/Messages/Play/Serverbound/SetDisplayedRecipe.hpp"
#include "protocolCraft/Messages/Play/Serverbound/SetRecipeBookState.hpp"
#endif

#include "protocolCraft/Messages/Play/Serverbound/ResourcePackStatus.hpp"
#include "protocolCraft/Messages/Play/Serverbound/AdvancementTab.hpp"
#include "protocolCraft/Messages/Play/Serverbound/HeldItemChangeServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/CreativeInventoryAction.hpp"
#include "protocolCraft/Messages/Play/Serverbound/UpdateSign.hpp"
#include "protocolCraft/Messages/Play/Serverbound/AnimationServerbound.hpp"
#include "protocolCraft/Messages/Play/Serverbound/Spectate.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PlayerBlockPlacement.hpp"
#include "protocolCraft/Messages/Play/Serverbound/UseItem.hpp"
#if PROTOCOL_VERSION > 388
#include "protocolCraft/Messages/Play/Serverbound/QueryBlockNBT.hpp"
#include "protocolCraft/Messages/Play/Serverbound/QueryEntityNBT.hpp"
#endif
#if PROTOCOL_VERSION > 385
#include "protocolCraft/Messages/Play/Serverbound/EditBook.hpp"
#include "protocolCraft/Messages/Play/Serverbound/PickItem.hpp"
#include "protocolCraft/Messages/Play/Serverbound/NameItem.hpp"
#include "protocolCraft/Messages/Play/Serverbound/SelectTrade.hpp"
#include "protocolCraft/Messages/Play/Serverbound/SetBeaconEffect.hpp"
#include "protocolCraft/Messages/Play/Serverbound/UpdateCommandBlock.hpp"
#include "protocolCraft/Messages/Play/Serverbound/UpdateCommandBlockMinecart.hpp"
#include "protocolCraft/Messages/Play/Serverbound/UpdateStructureBlock.hpp"
#endif
#if PROTOCOL_VERSION > 463
#include "protocolCraft/Messages/Play/Serverbound/SetDifficulty.hpp"
#include "protocolCraft/Messages/Play/Serverbound/LockDifficulty.hpp"
#endif
#if PROTOCOL_VERSION > 476
#include "protocolCraft/Messages/Play/Serverbound/ClickWindowButton.hpp"
#endif
#if PROTOCOL_VERSION > 471
#include "protocolCraft/Messages/Play/Serverbound/UpdateJigsawBlock.hpp"
#endif
#if PROTOCOL_VERSION > 711
#include "protocolCraft/Messages/Play/Serverbound/GenerateStructure.hpp"
#endif

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
#include "protocolCraft/Messages/Play/Clientbound/EntityMovement.hpp"
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
#if PROTOCOL_VERSION < 721
#include "protocolCraft/Messages/Play/Clientbound/SpawnGlobalEntity.hpp"
#endif
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
#include "protocolCraft/Messages/Play/Clientbound/UpdateScore.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SpawnPosition.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Title.hpp"
#include "protocolCraft/Messages/Play/Clientbound/SoundEffect.hpp"
#include "protocolCraft/Messages/Play/Clientbound/PlayerListHeaderAndFooter.hpp"
#include "protocolCraft/Messages/Play/Clientbound/CollectItem.hpp"
#include "protocolCraft/Messages/Play/Clientbound/Advancements.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityProperties.hpp"
#include "protocolCraft/Messages/Play/Clientbound/EntityEffect.hpp"
#if PROTOCOL_VERSION > 344
#include "protocolCraft/Messages/Play/Clientbound/DeclareCommands.hpp"
#endif
#if PROTOCOL_VERSION > 388
#include "protocolCraft/Messages/Play/Clientbound/NBTQueryResponse.hpp"
#endif
#if PROTOCOL_VERSION > 351
#include "protocolCraft/Messages/Play/Clientbound/FacePlayer.hpp"
#endif
#if PROTOCOL_VERSION > 342
#include "protocolCraft/Messages/Play/Clientbound/StopSound.hpp"
#endif
#if PROTOCOL_VERSION > 347
#include "protocolCraft/Messages/Play/Clientbound/DeclareRecipes.hpp"
#endif
#if PROTOCOL_VERSION > 348
#include "protocolCraft/Messages/Play/Clientbound/Tags.hpp"
#endif
#if PROTOCOL_VERSION > 451
#include "protocolCraft/Messages/Play/Clientbound/OpenHorseWindow.hpp"
#include "protocolCraft/Messages/Play/Clientbound/TradeList.hpp"
#endif
#if PROTOCOL_VERSION > 450
#include "protocolCraft/Messages/Play/Clientbound/OpenBook.hpp"
#endif
#if PROTOCOL_VERSION > 471
#include "protocolCraft/Messages/Play/Clientbound/UpdateViewPosition.hpp"
#include "protocolCraft/Messages/Play/Clientbound/UpdateViewDistance.hpp"
#endif
#if PROTOCOL_VERSION > 440
#include "protocolCraft/Messages/Play/Clientbound/EntitySoundEffect.hpp"
#endif


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

        // Status serverbound
        Request,
        Ping,

        // Status clientbound
        Response,
        Pong,


        // Play serverbound
        AdvancementTab,
        AnimationServerbound,
        ChatMessageServerbound,
        ClickWindow,
#if PROTOCOL_VERSION > 476
        ClickWindowButton,
#endif
        ClientSettings,
        ClientStatus,
        CloseWindowServerbound,
        ConfirmTransactionServerbound,
        CraftRecipeRequest,
        CreativeInventoryAction,
#if PROTOCOL_VERSION > 385
        EditBook,
#endif
#if PROTOCOL_VERSION < 476
        EnchantItem,
#endif
        EntityAction,
#if PROTOCOL_VERSION > 711
        GenerateStructure,
#endif
        HeldItemChangeServerbound,
        InteractEntity,
        KeepAliveServerbound,
#if PROTOCOL_VERSION > 463
        LockDifficulty,  
#endif
#if PROTOCOL_VERSION > 385
        NameItem,
        PickItem,
#endif
        PlayerAbilitiesServerbound,
        PlayerBlockPlacement,
        PlayerDigging,
        PlayerLook,
        PlayerMovement,
        PlayerPosition,
        PlayerPositionAndLookServerbound,
        PluginMessageServerbound,
#if PROTOCOL_VERSION > 388
        QueryBlockNBT,
        QueryEntityNBT,
#endif
#if PROTOCOL_VERSION < 736
        RecipeBookData,
#else
        SetDisplayedRecipe,
        SetRecipeBookState,
#endif
        ResourcePackStatus,
#if PROTOCOL_VERSION > 385
        SelectTrade,
        SetBeaconEffect,
#endif
#if PROTOCOL_VERSION > 463
        SetDifficulty,
#endif
        Spectate,
        SteerBoat,
        SteerVehicle,
        TabCompleteServerbound,
        TeleportConfirm,
#if PROTOCOL_VERSION > 385
        UpdateCommandBlock,
        UpdateCommandBlockMinecart,
#endif
#if PROTOCOL_VERSION > 471
        UpdateJigsawBlock,
#endif
        UpdateSign,
#if PROTOCOL_VERSION > 385
        UpdateStructureBlock,
#endif
        UseItem,
        VehicleMoveServerbound,

        // Play clientbound
        Advancements,
        AttachEntity,
        BlockAction,
        BlockBreakAnimation,
        BlockChange,
        BossBar,
        Camera,
        CloseWindowClientbound,
        CollectItem,
        CombatEvent,
        DestroyEntities,
#if PROTOCOL_VERSION > 345
        DeclareCommands,
#endif
#if PROTOCOL_VERSION > 347
        DeclareRecipes,
#endif
#if PROTOCOL_VERSION > 351
        FacePlayer,
#endif
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
#if PROTOCOL_VERSION > 388
        NBTQueryResponse,
#endif
        OpenSignEditor,
#if PROTOCOL_VERSION > 451
        OpenHorseWindow,
#endif
#if PROTOCOL_VERSION > 450
        OpenBook,
#endif
        ChunkData,
        JoinGame,
        Effect,
        EntityMovement,
        EntityAnimationClientbound,
        EntityEquipment,
        EntityEffect,
        EntityHeadLook,
        EntityRelativeMove,
        EntityLookAndRelativeMove,
        EntityLook,
        EntityMetadata,
        EntityProperties,
#if PROTOCOL_VERSION > 450
        EntitySoundEffect,
#endif
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
        Respawn,
#if PROTOCOL_VERSION > 404
        UpdateLight,
#endif
#if PROTOCOL_VERSION > 493
        AcknowledgePlayerDigging,
#endif
        UpdateBlockEntity,
        PlayerInfo,
        PlayerListHeaderAndFooter,
        PluginMessageClientbound,
        RemoveEntityEffect,
        RessourcePackSend,
        ScoreboardObjective,
        SelectAdvancementTab,
        SetExperience,
        SetSlot,
        SetCooldown,
        SetPassengers,
        SoundEffect,
        SpawnExperienceOrb,
#if PROTOCOL_VERSION < 721
        SpawnGlobalEntity,
#endif
        SpawnMob,
        SpawnObject,
        SpawnPainting,
        SpawnPlayer,
        SpawnPosition,
        Statistics,
#if PROTOCOL_VERSION > 342
        StopSound,
#endif
#if PROTOCOL_VERSION > 348
        Tags,
#endif
        TabCompleteClientbound,
        Teams,
        Title,
#if PROTOCOL_VERSION < 461
        UseBed,
#endif
#if PROTOCOL_VERSION > 451
        TradeList,
#endif
        UnlockRecipes,
        UpdateScore,
#if PROTOCOL_VERSION > 471
        UpdateViewPosition,
        UpdateViewDistance,
#endif
        VehicleMoveClientbound,
        WindowItems,
        WindowProperty,
        OpenWindow,
        HeldItemChangeClientbound,
        WorldBorder
    > ;
} //ProtocolCraft