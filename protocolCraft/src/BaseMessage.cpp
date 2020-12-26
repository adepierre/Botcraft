#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/AllMessages.hpp"
#include "protocolCraft/Handler.hpp"

namespace ProtocolCraft
{
    template <typename TDerived>
    void BaseMessage<TDerived>::DispatchImpl(Handler *handler)
    {
        handler->Handle(static_cast<TDerived&>(*this));
    }

    // Explicit instantiation for each message class
    // Handshaking serverbound
    template class BaseMessage<Handshake>;


    // Login serverbound
    template class BaseMessage<LoginStart>;
    template class BaseMessage<EncryptionResponse>;

    // Login clientbound
    template class BaseMessage<DisconnectLogin>;
    template class BaseMessage<EncryptionRequest>;
    template class BaseMessage<LoginSuccess>;
    template class BaseMessage<SetCompression>;

    // Status serverbound
    template class BaseMessage<Request>;
    template class BaseMessage<Ping>;

    // Status clientbound
    template class BaseMessage<Response>;
    template class BaseMessage<Pong>;


    // Play serverbound
    template class BaseMessage<AdvancementTab>;
    template class BaseMessage<AnimationServerbound>;
    template class BaseMessage<ChatMessageServerbound>;
    template class BaseMessage<ClickWindow>;
#if PROTOCOL_VERSION > 476
    template class BaseMessage<ClickWindowButton>;
#endif
    template class BaseMessage<ClientSettings>;
    template class BaseMessage<ClientStatus>;
    template class BaseMessage<CloseWindowServerbound>;
    template class BaseMessage<ConfirmTransactionServerbound>;
    template class BaseMessage<CraftRecipeRequest>;
    template class BaseMessage<CreativeInventoryAction>;
#if PROTOCOL_VERSION > 385
    template class BaseMessage<EditBook>;
#endif
#if PROTOCOL_VERSION < 476
    template class BaseMessage<EnchantItem>;
#endif
    template class BaseMessage<EntityAction>;
#if PROTOCOL_VERSION > 711
    template class BaseMessage<GenerateStructure>;
#endif
    template class BaseMessage<HeldItemChangeServerbound>;
    template class BaseMessage<InteractEntity>;
    template class BaseMessage<KeepAliveServerbound>;
#if PROTOCOL_VERSION > 463
    template class BaseMessage<LockDifficulty>;
#endif
#if PROTOCOL_VERSION > 385
    template class BaseMessage<NameItem>;
    template class BaseMessage<PickItem>;
#endif
    template class BaseMessage<PlayerAbilitiesServerbound>;
    template class BaseMessage<PlayerBlockPlacement>;
    template class BaseMessage<PlayerDigging>;
    template class BaseMessage<PlayerLook>;
    template class BaseMessage<PlayerMovement>;
    template class BaseMessage<PlayerPosition>;
    template class BaseMessage<PlayerPositionAndLookServerbound>;
    template class BaseMessage<PluginMessageServerbound>;
#if PROTOCOL_VERSION > 388
    template class BaseMessage<QueryBlockNBT>;
    template class BaseMessage<QueryEntityNBT>;
#endif
#if PROTOCOL_VERSION < 736
    template class BaseMessage<RecipeBookData>;
#else
    template class BaseMessage<SetDisplayedRecipe>;
    template class BaseMessage<SetRecipeBookState>;
#endif
    template class BaseMessage<ResourcePackStatus>;
#if PROTOCOL_VERSION > 385
    template class BaseMessage<SelectTrade>;
    template class BaseMessage<SetBeaconEffect>;
#endif
#if PROTOCOL_VERSION > 463
    template class BaseMessage<SetDifficulty>;
#endif
    template class BaseMessage<Spectate>;
    template class BaseMessage<SteerBoat>;
    template class BaseMessage<SteerVehicle>;
    template class BaseMessage<TabCompleteServerbound>;
    template class BaseMessage<TeleportConfirm>;
#if PROTOCOL_VERSION > 385
    template class BaseMessage<UpdateCommandBlock>;
    template class BaseMessage<UpdateCommandBlockMinecart>;
#endif
#if PROTOCOL_VERSION > 471
    template class BaseMessage<UpdateJigsawBlock>;
#endif
    template class BaseMessage<UpdateSign>;
#if PROTOCOL_VERSION > 385
    template class BaseMessage<UpdateStructureBlock>;
#endif
    template class BaseMessage<UseItem>;
    template class BaseMessage<VehicleMoveServerbound>;

    // Play clientbound
    template class BaseMessage<Advancements>;
    template class BaseMessage<AttachEntity>;
    template class BaseMessage<BlockAction>;
    template class BaseMessage<BlockBreakAnimation>;
    template class BaseMessage<BlockChange>;
    template class BaseMessage<BossBar>;
    template class BaseMessage<Camera>;
    template class BaseMessage<CloseWindowClientbound>;
    template class BaseMessage<CollectItem>;
    template class BaseMessage<CombatEvent>;
    template class BaseMessage<DestroyEntities>;
#if PROTOCOL_VERSION > 345
    template class BaseMessage<DeclareCommands>;
#endif
#if PROTOCOL_VERSION > 347
    template class BaseMessage<DeclareRecipes>;
#endif
#if PROTOCOL_VERSION > 351
    template class BaseMessage<FacePlayer>;
#endif
    template class BaseMessage<ServerDifficulty>;
    template class BaseMessage<MapData>;
    template class BaseMessage<MultiBlockChange>;
    template class BaseMessage<ConfirmTransactionClientbound>;
    template class BaseMessage<ChangeGameState>;
    template class BaseMessage<CraftRecipeResponse>;
    template class BaseMessage<DisconnectPlay>;
    template class BaseMessage<DisplayScoreboard>;
    template class BaseMessage<UnloadChunk>;
    template class BaseMessage<KeepAliveClientbound>;
    template class BaseMessage<NamedSoundEffect>;
#if PROTOCOL_VERSION > 388
    template class BaseMessage<NBTQueryResponse>;
#endif
    template class BaseMessage<OpenSignEditor>;
#if PROTOCOL_VERSION > 451
    template class BaseMessage<OpenHorseWindow>;
#endif
#if PROTOCOL_VERSION > 450
    template class BaseMessage<OpenBook>;
#endif
    template class BaseMessage<ChunkData>;
    template class BaseMessage<JoinGame>;
    template class BaseMessage<Effect>;
    template class BaseMessage<Entity>;
    template class BaseMessage<EntityAnimationClientbound>;
    template class BaseMessage<EntityEquipment>;
    template class BaseMessage<EntityEffect>;
    template class BaseMessage<EntityHeadLook>;
    template class BaseMessage<EntityRelativeMove>;
    template class BaseMessage<EntityLookAndRelativeMove>;
    template class BaseMessage<EntityLook>;
    template class BaseMessage<EntityMetadata>;
    template class BaseMessage<EntityProperties>;
#if PROTOCOL_VERSION > 450
    template class BaseMessage<EntitySoundEffect>;
#endif
    template class BaseMessage<EntityStatus>;
    template class BaseMessage<EntityVelocity>;
    template class BaseMessage<Explosion>;
    template class BaseMessage<Particle>;
    template class BaseMessage<PlayerPositionAndLookClientbound>;
    template class BaseMessage<UpdateHealth>;
    template class BaseMessage<EntityTeleport>;
    template class BaseMessage<PlayerAbilitiesClientbound>;
    template class BaseMessage<TimeUpdate>;
    template class BaseMessage<ChatMessageClientbound>;
    template class BaseMessage<Respawn>;
#if PROTOCOL_VERSION > 404
    template class BaseMessage<UpdateLight>;
#endif
#if PROTOCOL_VERSION > 493
    template class BaseMessage<AcknowledgePlayerDigging>;
#endif
    template class BaseMessage<UpdateBlockEntity>;
    template class BaseMessage<PlayerInfo>;
    template class BaseMessage<PlayerListHeaderAndFooter>;
    template class BaseMessage<PluginMessageClientbound>;
    template class BaseMessage<RemoveEntityEffect>;
    template class BaseMessage<RessourcePackSend>;
    template class BaseMessage<ScoreboardObjective>;
    template class BaseMessage<SelectAdvancementTab>;
    template class BaseMessage<SetExperience>;
    template class BaseMessage<SetSlot>;
    template class BaseMessage<SetCooldown>;
    template class BaseMessage<SetPassengers>;
    template class BaseMessage<SoundEffect>;
    template class BaseMessage<SpawnExperienceOrb>;
#if PROTOCOL_VERSION < 721
    template class BaseMessage<SpawnGlobalEntity>;
#endif
    template class BaseMessage<SpawnMob>;
    template class BaseMessage<SpawnObject>;
    template class BaseMessage<SpawnPainting>;
    template class BaseMessage<SpawnPlayer>;
    template class BaseMessage<SpawnPosition>;
    template class BaseMessage<Statistics>;
#if PROTOCOL_VERSION > 342
    template class BaseMessage<StopSound>;
#endif
#if PROTOCOL_VERSION > 348
    template class BaseMessage<Tags>;
#endif
    template class BaseMessage<TabCompleteClientbound>;
    template class BaseMessage<Teams>;
    template class BaseMessage<Title>;
#if PROTOCOL_VERSION < 461
    template class BaseMessage<UseBed>;
#endif
#if PROTOCOL_VERSION > 451
    template class BaseMessage<TradeList>;
#endif
    template class BaseMessage<UnlockRecipes>;
    template class BaseMessage<UpdateScore>;
#if PROTOCOL_VERSION > 471
    template class BaseMessage<UpdateViewPosition>;
    template class BaseMessage<UpdateViewDistance>;
#endif
    template class BaseMessage<VehicleMoveClientbound>;
    template class BaseMessage<WindowItems>;
    template class BaseMessage<WindowProperty>;
    template class BaseMessage<OpenWindow>;
    template class BaseMessage<HeldItemChangeClientbound>;
    template class BaseMessage<WorldBorder>;
}