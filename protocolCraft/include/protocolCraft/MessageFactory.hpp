#pragma once

#include <memory>

#include "protocolCraft/AllMessages.hpp"
#include "protocolCraft/enums.hpp"

namespace ProtocolCraft
{
    class MessageFactory
    {
    public:
        static std::shared_ptr<Message> CreateMessageClientbound(const int id, const ConnectionState state)
        {
            switch (state)
            {
            case ConnectionState::None:
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Handshake:
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Status:
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Login: // Login
                switch (id)
                {
                case 0x00:
                    return std::shared_ptr<DisconnectLogin>(new DisconnectLogin);
                    break;
                case 0x01:
                    return std::shared_ptr<EncryptionRequest>(new EncryptionRequest);
                    break;
                case 0x02:
                    return std::shared_ptr<LoginSuccess>(new LoginSuccess);
                    break;
                case 0x03:
                    return std::shared_ptr<SetCompression>(new SetCompression);
                    break;
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Play:
                switch (id)
                {
#if PROTOCOL_VERSION == 340 // 1.12.2
                case 0x00:
                    return std::shared_ptr<SpawnObject>(new SpawnObject);
                    break;
                case 0x01:
                    return std::shared_ptr<SpawnExperienceOrb>(new SpawnExperienceOrb);
                    break;
                case 0x02:
                    return std::shared_ptr<SpawnGlobalEntity>(new SpawnGlobalEntity);
                    break;
                case 0x03:
                    return std::shared_ptr<SpawnMob>(new SpawnMob);
                    break;
                case 0x04:
                    return std::shared_ptr<SpawnPainting>(new SpawnPainting);
                    break;
                case 0x05:
                    return std::shared_ptr<SpawnPlayer>(new SpawnPlayer);
                    break;
                case 0x06:
                    return std::shared_ptr<EntityAnimationClientbound>(new EntityAnimationClientbound);
                    break;
                case 0x07:
                    return std::shared_ptr<Statistics>(new Statistics);
                    break;
                case 0x08:
                    return std::shared_ptr<BlockBreakAnimation>(new BlockBreakAnimation);
                    break;
                case 0x09:
                    return std::shared_ptr<UpdateBlockEntity>(new UpdateBlockEntity);
                    break;
                case 0x0A:
                    return std::shared_ptr<BlockAction>(new BlockAction);
                    break;
                case 0x0B:
                    return std::shared_ptr<BlockChange>(new BlockChange);
                    break;
                case 0x0C:
                    return std::shared_ptr<BossBar>(new BossBar);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerDifficulty>(new ServerDifficulty);
                    break;
                case 0x0E:
                    return std::shared_ptr<TabCompleteClientbound>(new TabCompleteClientbound);
                    break;
                case 0x0F:
                    return std::shared_ptr<ChatMessageClientbound>(new ChatMessageClientbound);
                    break;
                case 0x10:
                    return std::shared_ptr<MultiBlockChange>(new MultiBlockChange);
                    break;
                case 0x11:
                    return std::shared_ptr<ConfirmTransactionClientbound>(new ConfirmTransactionClientbound);
                    break;
                case 0x12:
                    return std::shared_ptr<CloseWindowClientbound>(new CloseWindowClientbound);
                    break;
                case 0x13:
                    return std::shared_ptr<OpenWindow>(new OpenWindow);
                    break;
                case 0x14:
                    return std::shared_ptr<WindowItems>(new WindowItems);
                    break;
                case 0x15:
                    return std::shared_ptr<WindowProperty>(new WindowProperty);
                    break;
                case 0x16:
                    return std::shared_ptr<SetSlot>(new SetSlot);
                    break;
                case 0x17:
                    return std::shared_ptr<SetCooldown>(new SetCooldown);
                    break;
                case 0x18:
                    return std::shared_ptr<PluginMessageClientbound>(new PluginMessageClientbound);
                    break;
                case 0x19:
                    return std::shared_ptr<NamedSoundEffect>(new NamedSoundEffect);
                    break;
                case 0x1A:
                    return std::shared_ptr<DisconnectPlay>(new DisconnectPlay);
                    break;
                case 0x1B:
                    return std::shared_ptr<EntityStatus>(new EntityStatus);
                    break;
                case 0x1C:
                    return std::shared_ptr<Explosion>(new Explosion);
                    break;
                case 0x1D:
                    return std::shared_ptr<UnloadChunk>(new UnloadChunk);
                    break;
                case 0x1E:
                    return std::shared_ptr<ChangeGameState>(new ChangeGameState);
                    break;
                case 0x1F:
                    return std::shared_ptr<KeepAliveClientbound>(new KeepAliveClientbound);
                    break;
                case 0x20:
                    return std::shared_ptr<ChunkData>(new ChunkData);
                    break;
                case 0x21:
                    return std::shared_ptr<Effect>(new Effect);
                    break;
                case 0x22:
                    return std::shared_ptr<Particle>(new Particle);
                    break;
                case 0x23:
                    return std::shared_ptr<JoinGame>(new JoinGame);
                    break;
                case 0x24:
                    return std::shared_ptr<MapData>(new MapData);
                    break;
                case 0x25:
                    return std::shared_ptr<Entity>(new Entity);
                    break;
                case 0x26:
                    return std::shared_ptr<EntityRelativeMove>(new EntityRelativeMove);
                    break;
                case 0x27:
                    return std::shared_ptr<EntityLookAndRelativeMove>(new EntityLookAndRelativeMove);
                    break;
                case 0x28:
                    return std::shared_ptr<EntityLook>(new EntityLook);
                    break;
                case 0x29:
                    return std::shared_ptr<VehicleMoveClientbound>(new VehicleMoveClientbound);
                    break;
                case 0x2A:
                    return std::shared_ptr<OpenSignEditor>(new OpenSignEditor);
                    break;
                case 0x2B:
                    return std::shared_ptr<CraftRecipeResponse>(new CraftRecipeResponse);
                    break;
                case 0x2C:
                    return std::shared_ptr<PlayerAbilitiesClientbound>(new PlayerAbilitiesClientbound);
                    break;
                case 0x2D:
                    return std::shared_ptr<CombatEvent>(new CombatEvent);
                    break;
                case 0x2E:
                    return std::shared_ptr<PlayerInfo>(new PlayerInfo);
                    break;
                case 0x2F:
                    return std::shared_ptr<PlayerPositionAndLookClientbound>(new PlayerPositionAndLookClientbound);
                    break;
                case 0x30:
                    return std::shared_ptr<UseBed>(new UseBed);
                    break;
                case 0x31:
                    return std::shared_ptr<UnlockRecipes>(new UnlockRecipes);
                    break;
                case 0x32:
                    return std::shared_ptr<DestroyEntities>(new DestroyEntities);
                    break;
                case 0x33:
                    return std::shared_ptr<RemoveEntityEffect>(new RemoveEntityEffect);
                    break;
                case 0x34:
                    return std::shared_ptr<RessourcePackSend>(new RessourcePackSend);
                    break;
                case 0x35:
                    return std::shared_ptr<Respawn>(new Respawn);
                    break;
                case 0x36:
                    return std::shared_ptr<EntityHeadLook>(new EntityHeadLook);
                    break;
                case 0x37:
                    return std::shared_ptr<SelectAdvancementTab>(new SelectAdvancementTab);
                    break;
                case 0x38:
                    return std::shared_ptr<WorldBorder>(new WorldBorder);
                    break;
                case 0x39:
                    return std::shared_ptr<Camera>(new Camera);
                    break;
                case 0x3A:
                    return std::shared_ptr<HeldItemChangeClientbound>(new HeldItemChangeClientbound);
                    break;
                case 0x3B:
                    return std::shared_ptr<DisplayScoreboard>(new DisplayScoreboard);
                    break;
                case 0x3C:
                    return std::shared_ptr<EntityMetadata>(new EntityMetadata);
                    break;
                case 0x3D:
                    return std::shared_ptr<AttachEntity>(new AttachEntity);
                    break;
                case 0x3E:
                    return std::shared_ptr<EntityVelocity>(new EntityVelocity);
                    break;
                case 0x3F:
                    return std::shared_ptr<EntityEquipment>(new EntityEquipment);
                    break;
                case 0x40:
                    return std::shared_ptr<SetExperience>(new SetExperience);
                    break;
                case 0x41:
                    return std::shared_ptr<UpdateHealth>(new UpdateHealth);
                    break;
                case 0x42:
                    return std::shared_ptr<ScoreboardObjective>(new ScoreboardObjective);
                    break;
                case 0x43:
                    return std::shared_ptr<SetPassengers>(new SetPassengers);
                    break;
                case 0x44:
                    return std::shared_ptr<Teams>(new Teams);
                    break;
                case 0x47:
                    return std::shared_ptr<TimeUpdate>(new TimeUpdate);
                    break;
                case 0x4C:
                    return std::shared_ptr<EntityTeleport>(new EntityTeleport);
                    break;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
                case 0x00:
                    return std::shared_ptr<SpawnObject>(new SpawnObject);
                    break;
                case 0x01:
                    return std::shared_ptr<SpawnExperienceOrb>(new SpawnExperienceOrb);
                    break;
                case 0x02:
                    return std::shared_ptr<SpawnGlobalEntity>(new SpawnGlobalEntity);
                    break;
                case 0x03:
                    return std::shared_ptr<SpawnMob>(new SpawnMob);
                    break;
                case 0x04:
                    return std::shared_ptr<SpawnPainting>(new SpawnPainting);
                    break;
                case 0x05:
                    return std::shared_ptr<SpawnPlayer>(new SpawnPlayer);
                    break;
                case 0x06:
                    return std::shared_ptr<EntityAnimationClientbound>(new EntityAnimationClientbound);
                    break;
                case 0x07:
                    return std::shared_ptr<Statistics>(new Statistics);
                    break;
                case 0x08:
                    return std::shared_ptr<BlockBreakAnimation>(new BlockBreakAnimation);
                    break;
				case 0x09:
					return std::shared_ptr<UpdateBlockEntity>(new UpdateBlockEntity);
					break;
                case 0x0A:
                    return std::shared_ptr<BlockAction>(new BlockAction);
                    break;
				case 0x0B:
                    return std::shared_ptr<BlockChange>(new BlockChange);
                    break;
                case 0x0C:
                    return std::shared_ptr<BossBar>(new BossBar);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerDifficulty>(new ServerDifficulty);
                    break;
                case 0x0E:
                    return std::shared_ptr<ChatMessageClientbound>(new ChatMessageClientbound);
                    break;
                case 0x0F:
                    return std::shared_ptr<MultiBlockChange>(new MultiBlockChange);
                    break;
                case 0x10:
                    return std::shared_ptr<TabCompleteClientbound>(new TabCompleteClientbound);
                    break;
                case 0x12:
                    return std::shared_ptr<ConfirmTransactionClientbound>(new ConfirmTransactionClientbound);
                    break;
                case 0x13:
                    return std::shared_ptr<CloseWindowClientbound>(new CloseWindowClientbound);
                    break;
                case 0x14:
                    return std::shared_ptr<OpenWindow>(new OpenWindow);
                    break;
                case 0x15:
                    return std::shared_ptr<WindowItems>(new WindowItems);
                    break;
                case 0x16:
                    return std::shared_ptr<WindowProperty>(new WindowProperty);
                    break;
                case 0x17:
                    return std::shared_ptr<SetSlot>(new SetSlot);
                    break;
                case 0x18:
                    return std::shared_ptr<SetCooldown>(new SetCooldown);
                    break;
                case 0x19:
                    return std::shared_ptr<PluginMessageClientbound>(new PluginMessageClientbound);
                    break;
                case 0x1A:
                    return std::shared_ptr<NamedSoundEffect>(new NamedSoundEffect);
                    break;
                case 0x1B:
                    return std::shared_ptr<DisconnectPlay>(new DisconnectPlay);
                    break;
                case 0x1C:
                    return std::shared_ptr<EntityStatus>(new EntityStatus);
                    break;
                case 0x1E:
                    return std::shared_ptr<Explosion>(new Explosion);
                    break;
                case 0x1F:
                    return std::shared_ptr<UnloadChunk>(new UnloadChunk);
                    break;
                case 0x20:
                    return std::shared_ptr<ChangeGameState>(new ChangeGameState);
                    break;
                case 0x21:
                    return std::shared_ptr<KeepAliveClientbound>(new KeepAliveClientbound);
                    break;
                case 0x22:
                    return std::shared_ptr<ChunkData>(new ChunkData);
                    break;
                case 0x23:
                    return std::shared_ptr<Effect>(new Effect);
                    break;
                case 0x24:
                    return std::shared_ptr<Particle>(new Particle);
                    break;
                case 0x25:
                    return std::shared_ptr<JoinGame>(new JoinGame);
                    break;
                case 0x26:
                    return std::shared_ptr<MapData>(new MapData);
                    break;
                case 0x27:
                    return std::shared_ptr<Entity>(new Entity);
                    break;
                case 0x28:
                    return std::shared_ptr<EntityRelativeMove>(new EntityRelativeMove);
                    break;
                case 0x29:
                    return std::shared_ptr<EntityLookAndRelativeMove>(new EntityLookAndRelativeMove);
                    break;
                case 0x2A:
                    return std::shared_ptr<EntityLook>(new EntityLook);
                    break;
                case 0x2B:
                    return std::shared_ptr<VehicleMoveClientbound>(new VehicleMoveClientbound);
                    break;
                case 0x2C:
                    return std::shared_ptr<OpenSignEditor>(new OpenSignEditor);
                    break;
                case 0x2D:
                    return std::shared_ptr<CraftRecipeResponse>(new CraftRecipeResponse);
                    break;
                case 0x2E:
                    return std::shared_ptr<PlayerAbilitiesClientbound>(new PlayerAbilitiesClientbound);
                    break;
                case 0x2F:
                    return std::shared_ptr<CombatEvent>(new CombatEvent);
                    break;
                case 0x30:
                    return std::shared_ptr<PlayerInfo>(new PlayerInfo);
                    break;
                case 0x32:
                    return std::shared_ptr<PlayerPositionAndLookClientbound>(new PlayerPositionAndLookClientbound);
                    break;
                case 0x33:
                    return std::shared_ptr<UseBed>(new UseBed);
                    break;
                case 0x34:
                    return std::shared_ptr<UnlockRecipes>(new UnlockRecipes);
                    break;
                case 0x35:
                    return std::shared_ptr<DestroyEntities>(new DestroyEntities);
                    break;
                case 0x36:
                    return std::shared_ptr<RemoveEntityEffect>(new RemoveEntityEffect);
                    break;
                case 0x37:
                    return std::shared_ptr<RessourcePackSend>(new RessourcePackSend);
                    break;
                case 0x38:
                    return std::shared_ptr<Respawn>(new Respawn);
                    break;
                case 0x39:
                    return std::shared_ptr<EntityHeadLook>(new EntityHeadLook);
                    break;
                case 0x3A:
                    return std::shared_ptr<SelectAdvancementTab>(new SelectAdvancementTab);
                    break;
                case 0x3B:
                    return std::shared_ptr<WorldBorder>(new WorldBorder);
                    break;
                case 0x3C:
                    return std::shared_ptr<Camera>(new Camera);
                    break;
                case 0x3D:
                    return std::shared_ptr<HeldItemChangeClientbound>(new HeldItemChangeClientbound);
                    break;
                case 0x3E:
                    return std::shared_ptr<DisplayScoreboard>(new DisplayScoreboard);
                    break;
                case 0x3F:
                    return std::shared_ptr<EntityMetadata>(new EntityMetadata);
                    break;
                case 0x40:
                    return std::shared_ptr<AttachEntity>(new AttachEntity);
                    break;
                case 0x41:
                    return std::shared_ptr<EntityVelocity>(new EntityVelocity);
                    break;
                case 0x42:
                    return std::shared_ptr<EntityEquipment>(new EntityEquipment);
                    break;
                case 0x43:
                    return std::shared_ptr<SetExperience>(new SetExperience);
                    break;
                case 0x44:
                    return std::shared_ptr<UpdateHealth>(new UpdateHealth);
                    break;
                case 0x45:
                    return std::shared_ptr<ScoreboardObjective>(new ScoreboardObjective);
                    break;
                case 0x46:
                    return std::shared_ptr<SetPassengers>(new SetPassengers);
                    break;
                case 0x47:
                    return std::shared_ptr<Teams>(new Teams);
                    break;
                case 0x4A:
                    return std::shared_ptr<TimeUpdate>(new TimeUpdate);
                    break;
                case 0x50:
                    return std::shared_ptr<EntityTeleport>(new EntityTeleport);
                    break;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
                case 0x00:
                    return std::shared_ptr<SpawnObject>(new SpawnObject);
                    break;
                case 0x01:
                    return std::shared_ptr<SpawnExperienceOrb>(new SpawnExperienceOrb);
                    break;
                case 0x02:
                    return std::shared_ptr<SpawnGlobalEntity>(new SpawnGlobalEntity);
                    break;
                case 0x03:
                    return std::shared_ptr<SpawnMob>(new SpawnMob);
                    break;
                case 0x04:
                    return std::shared_ptr<SpawnPainting>(new SpawnPainting);
                    break;
                case 0x05:
                    return std::shared_ptr<SpawnPlayer>(new SpawnPlayer);
                    break;
                case 0x06:
                    return std::shared_ptr<EntityAnimationClientbound>(new EntityAnimationClientbound);
                    break;
                case 0x07:
                    return std::shared_ptr<Statistics>(new Statistics);
                    break;
                case 0x08:
                    return std::shared_ptr<BlockBreakAnimation>(new BlockBreakAnimation);
                    break;
				case 0x09:
					return std::shared_ptr<UpdateBlockEntity>(new UpdateBlockEntity);
				    break;
                case 0x0A:
                    return std::shared_ptr<BlockAction>(new BlockAction);
                    break;
				case 0x0B:
                    return std::shared_ptr<BlockChange>(new BlockChange);
                    break;
                case 0x0C:
                    return std::shared_ptr<BossBar>(new BossBar);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerDifficulty>(new ServerDifficulty);
                    break;
                case 0x0E:
                    return std::shared_ptr<ChatMessageClientbound>(new ChatMessageClientbound);
                    break;
                case 0x0F:
                    return std::shared_ptr<MultiBlockChange>(new MultiBlockChange);
                    break;
                case 0x10:
                    return std::shared_ptr<TabCompleteClientbound>(new TabCompleteClientbound);
                    break;
                case 0x12:
                    return std::shared_ptr<ConfirmTransactionClientbound>(new ConfirmTransactionClientbound);
                    break;
                case 0x13:
                    return std::shared_ptr<CloseWindowClientbound>(new CloseWindowClientbound);
                    break;
                case 0x14:
                    return std::shared_ptr<WindowItems>(new WindowItems);
                    break;
                case 0x15:
                    return std::shared_ptr<WindowProperty>(new WindowProperty);
                    break;
                case 0x16:
                    return std::shared_ptr<SetSlot>(new SetSlot);
                    break;
                case 0x17:
                    return std::shared_ptr<SetCooldown>(new SetCooldown);
                    break;
                case 0x18:
                    return std::shared_ptr<PluginMessageClientbound>(new PluginMessageClientbound);
                    break;
                case 0x19:
                    return std::shared_ptr<NamedSoundEffect>(new NamedSoundEffect);
                    break;
                case 0x1A:
                    return std::shared_ptr<DisconnectPlay>(new DisconnectPlay);
                    break;
                case 0x1B:
                    return std::shared_ptr<EntityStatus>(new EntityStatus);
                    break;
                case 0x1C:
                    return std::shared_ptr<Explosion>(new Explosion);
                    break;
                case 0x1D:
                    return std::shared_ptr<UnloadChunk>(new UnloadChunk);
                    break;
                case 0x1E:
                    return std::shared_ptr<ChangeGameState>(new ChangeGameState);
                    break;
                case 0x20:
                    return std::shared_ptr<KeepAliveClientbound>(new KeepAliveClientbound);
                    break;
                case 0x21:
                    return std::shared_ptr<ChunkData>(new ChunkData);
                    break;
                case 0x22:
                    return std::shared_ptr<Effect>(new Effect);
                    break;
                case 0x23:
                    return std::shared_ptr<Particle>(new Particle);
                    break;
                case 0x24:
                    return std::shared_ptr<UpdateLight>(new UpdateLight);
                    break;
                case 0x25:
                    return std::shared_ptr<JoinGame>(new JoinGame);
                    break;
                case 0x26:
                    return std::shared_ptr<MapData>(new MapData);
                    break;
                case 0x28:
                    return std::shared_ptr<EntityRelativeMove>(new EntityRelativeMove);
                    break;
                case 0x29:
                    return std::shared_ptr<EntityLookAndRelativeMove>(new EntityLookAndRelativeMove);
                    break;
                case 0x2A:
                    return std::shared_ptr<EntityLook>(new EntityLook);
                    break;
                case 0x2B:
                    return std::shared_ptr<Entity>(new Entity);
                    break;
                case 0x2C:
                    return std::shared_ptr<VehicleMoveClientbound>(new VehicleMoveClientbound);
                    break;
                case 0x2E:
                    return std::shared_ptr<OpenWindow>(new OpenWindow);
                    break;
                case 0x2F:
                    return std::shared_ptr<OpenSignEditor>(new OpenSignEditor);
                    break;
                case 0x30:
                    return std::shared_ptr<CraftRecipeResponse>(new CraftRecipeResponse);
                    break;
                case 0x31:
                    return std::shared_ptr<PlayerAbilitiesClientbound>(new PlayerAbilitiesClientbound);
                    break;
                case 0x32:
                    return std::shared_ptr<CombatEvent>(new CombatEvent);
                    break;
                case 0x33:
                    return std::shared_ptr<PlayerInfo>(new PlayerInfo);
                    break;
                case 0x35:
                    return std::shared_ptr<PlayerPositionAndLookClientbound>(new PlayerPositionAndLookClientbound);
                    break;
                case 0x36:
                    return std::shared_ptr<UnlockRecipes>(new UnlockRecipes);
                    break;
                case 0x37:
                    return std::shared_ptr<DestroyEntities>(new DestroyEntities);
                    break;
                case 0x38:
                    return std::shared_ptr<RemoveEntityEffect>(new RemoveEntityEffect);
                    break;
                case 0x39:
                    return std::shared_ptr<RessourcePackSend>(new RessourcePackSend);
                    break;
                case 0x3A:
                    return std::shared_ptr<Respawn>(new Respawn);
                    break;
                case 0x3B:
                    return std::shared_ptr<EntityHeadLook>(new EntityHeadLook);
                    break;
                case 0x3C:
                    return std::shared_ptr<SelectAdvancementTab>(new SelectAdvancementTab);
                    break;
                case 0x3D:
                    return std::shared_ptr<WorldBorder>(new WorldBorder);
                    break;
                case 0x3E:
                    return std::shared_ptr<Camera>(new Camera);
                    break;
                case 0x3F:
                    return std::shared_ptr<HeldItemChangeClientbound>(new HeldItemChangeClientbound);
                    break;
                case 0x42:
                    return std::shared_ptr<DisplayScoreboard>(new DisplayScoreboard);
                    break;
                case 0x43:
                    return std::shared_ptr<EntityMetadata>(new EntityMetadata);
                    break;
                case 0x44:
                    return std::shared_ptr<AttachEntity>(new AttachEntity);
                    break;
                case 0x45:
                    return std::shared_ptr<EntityVelocity>(new EntityVelocity);
                    break;
                case 0x46:
                    return std::shared_ptr<EntityEquipment>(new EntityEquipment);
                    break;
                case 0x47:
                    return std::shared_ptr<SetExperience>(new SetExperience);
                    break;
                case 0x48:
                    return std::shared_ptr<UpdateHealth>(new UpdateHealth);
                    break;
                case 0x49:
                    return std::shared_ptr<ScoreboardObjective>(new ScoreboardObjective);
                    break;
                case 0x4A:
                    return std::shared_ptr<SetPassengers>(new SetPassengers);
                    break;
                case 0x4B:
                    return std::shared_ptr<Teams>(new Teams);
                    break;
                case 0x4E:
                    return std::shared_ptr<TimeUpdate>(new TimeUpdate);
                    break;
                case 0x56:
                    return std::shared_ptr<EntityTeleport>(new EntityTeleport);
                    break;
#if PROTOCOL_VERSION > 493
                case 0x5C:
                    return std::shared_ptr<AcknowledgePlayerDigging>(new AcknowledgePlayerDigging);
                    break;
#endif
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
                case 0x00:
                    return std::shared_ptr<SpawnObject>(new SpawnObject);
                    break;
                case 0x01:
                    return std::shared_ptr<SpawnExperienceOrb>(new SpawnExperienceOrb);
                    break;
                case 0x02:
                    return std::shared_ptr<SpawnGlobalEntity>(new SpawnGlobalEntity);
                    break;
                case 0x03:
                    return std::shared_ptr<SpawnMob>(new SpawnMob);
                    break;
                case 0x04:
                    return std::shared_ptr<SpawnPainting>(new SpawnPainting);
                    break;
                case 0x05:
                    return std::shared_ptr<SpawnPlayer>(new SpawnPlayer);
                    break;
                case 0x06:
                    return std::shared_ptr<EntityAnimationClientbound>(new EntityAnimationClientbound);
                    break;
                case 0x07:
                    return std::shared_ptr<Statistics>(new Statistics);
                    break;
				case 0x08:
					return std::shared_ptr<AcknowledgePlayerDigging>(new AcknowledgePlayerDigging);
					break;
                case 0x09:
                    return std::shared_ptr<BlockBreakAnimation>(new BlockBreakAnimation);
                    break;
                case 0x0A:
                    return std::shared_ptr<UpdateBlockEntity>(new UpdateBlockEntity);
                    break;
                case 0x0B:
                    return std::shared_ptr<BlockAction>(new BlockAction);
                    break;
				case 0x0C:
					return std::shared_ptr<BlockChange>(new BlockChange);
					break;
                case 0x0D:
                    return std::shared_ptr<BossBar>(new BossBar);
                    break;
				case 0x0E:
					return std::shared_ptr<ServerDifficulty>(new ServerDifficulty);
					break;
				case 0x0F:
					return std::shared_ptr<ChatMessageClientbound>(new ChatMessageClientbound);
					break;
				case 0x10:
					return std::shared_ptr<MultiBlockChange>(new MultiBlockChange);
					break;
                case 0x11:
                    return std::shared_ptr<TabCompleteClientbound>(new TabCompleteClientbound);
                    break;
				case 0x13:
					return std::shared_ptr<ConfirmTransactionClientbound>(new ConfirmTransactionClientbound);
					break;
                case 0x14:
                    return std::shared_ptr<CloseWindowClientbound>(new CloseWindowClientbound);
                    break;
				case 0x15:
					return std::shared_ptr<WindowItems>(new WindowItems);
					break;
                case 0x16:
                    return std::shared_ptr<WindowProperty>(new WindowProperty);
                    break;
				case 0x17:
					return std::shared_ptr<SetSlot>(new SetSlot);
					break;
                case 0x18:
                    return std::shared_ptr<SetCooldown>(new SetCooldown);
                    break;
                case 0x19:
                    return std::shared_ptr<PluginMessageClientbound>(new PluginMessageClientbound);
                    break;
                case 0x1A:
                    return std::shared_ptr<NamedSoundEffect>(new NamedSoundEffect);
                    break;
				case 0x1B:
					return std::shared_ptr<DisconnectPlay>(new DisconnectPlay);
					break;
                case 0x1C:
                    return std::shared_ptr<EntityStatus>(new EntityStatus);
                    break;
                case 0x1D:
                    return std::shared_ptr<Explosion>(new Explosion);
                    break;
				case 0x1E:
					return std::shared_ptr<UnloadChunk>(new UnloadChunk);
					break;
                case 0x1F:
                    return std::shared_ptr<ChangeGameState>(new ChangeGameState);
                    break;
				case 0x21:
					return std::shared_ptr<KeepAliveClientbound>(new KeepAliveClientbound);
					break;
				case 0x22:
					return std::shared_ptr<ChunkData>(new ChunkData);
					break;
                case 0x23:
                    return std::shared_ptr<Effect>(new Effect);
                    break;
                case 0x24:
                    return std::shared_ptr<Particle>(new Particle);
                    break;
				case 0x25:
					return std::shared_ptr<UpdateLight>(new UpdateLight);
					break;
				case 0x26:
					return std::shared_ptr<JoinGame>(new JoinGame);
					break;
                case 0x27:
                    return std::shared_ptr<MapData>(new MapData);
                    break;
                case 0x29:
                    return std::shared_ptr<EntityRelativeMove>(new EntityRelativeMove);
                    break;
				case 0x2C:
					return std::shared_ptr<Entity>(new Entity);
					break;
				case 0x2A:
					return std::shared_ptr<EntityLookAndRelativeMove>(new EntityLookAndRelativeMove);
					break;
				case 0x2B:
					return std::shared_ptr<EntityLook>(new EntityLook);
					break;
                case 0x2D:
                    return std::shared_ptr<VehicleMoveClientbound>(new VehicleMoveClientbound);
                    break;
                case 0x2F:
                    return std::shared_ptr<OpenWindow>(new OpenWindow);
                    break;
                case 0x30:
                    return std::shared_ptr<OpenSignEditor>(new OpenSignEditor);
                    break;
                case 0x31:
                    return std::shared_ptr<CraftRecipeResponse>(new CraftRecipeResponse);
                    break;
				case 0x32:
					return std::shared_ptr<PlayerAbilitiesClientbound>(new PlayerAbilitiesClientbound);
					break;
                case 0x33:
                    return std::shared_ptr<CombatEvent>(new CombatEvent);
                    break;
				case 0x34:
					return std::shared_ptr<PlayerInfo>(new PlayerInfo);
					break;
				case 0x36:
					return std::shared_ptr<PlayerPositionAndLookClientbound>(new PlayerPositionAndLookClientbound);
					break;
                case 0x37:
                    return std::shared_ptr<UnlockRecipes>(new UnlockRecipes);
                    break;
                case 0x38:
                    return std::shared_ptr<DestroyEntities>(new DestroyEntities);
                    break;
                case 0x39:
                    return std::shared_ptr<RemoveEntityEffect>(new RemoveEntityEffect);
                    break;
                case 0x3A:
                    return std::shared_ptr<RessourcePackSend>(new RessourcePackSend);
                    break;
				case 0x3B:
					return std::shared_ptr<Respawn>(new Respawn);
					break;
                case 0x3C:
                    return std::shared_ptr<EntityHeadLook>(new EntityHeadLook);
                    break;
                case 0x3D:
                    return std::shared_ptr<SelectAdvancementTab>(new SelectAdvancementTab);
                    break;
                case 0x3E:
                    return std::shared_ptr<WorldBorder>(new WorldBorder);
                    break;
                case 0x3F:
                    return std::shared_ptr<Camera>(new Camera);
                    break;
				case 0x40:
					return std::shared_ptr<HeldItemChangeClientbound>(new HeldItemChangeClientbound);
					break;
                case 0x43:
                    return std::shared_ptr<DisplayScoreboard>(new DisplayScoreboard);
                    break;
                case 0x44:
                    return std::shared_ptr<EntityMetadata>(new EntityMetadata);
                    break;
                case 0x45:
                    return std::shared_ptr<AttachEntity>(new AttachEntity);
                    break;
                case 0x46:
                    return std::shared_ptr<EntityVelocity>(new EntityVelocity);
                    break;
                case 0x47:
                    return std::shared_ptr<EntityEquipment>(new EntityEquipment);
                    break;
                case 0x48:
                    return std::shared_ptr<SetExperience>(new SetExperience);
                    break;
                case 0x49:
                    return std::shared_ptr<UpdateHealth>(new UpdateHealth);
                    break;
                case 0x4A:
                    return std::shared_ptr<ScoreboardObjective>(new ScoreboardObjective);
                    break;
                case 0x4B:
                    return std::shared_ptr<SetPassengers>(new SetPassengers);
                    break;
                case 0x4C:
                    return std::shared_ptr<Teams>(new Teams);
                    break;
				case 0x4F:
					return std::shared_ptr<TimeUpdate>(new TimeUpdate);
					break;
				case 0x57:
					return std::shared_ptr<EntityTeleport>(new EntityTeleport);
					break;
#else
                #error "Protocol version not implemented"
#endif
                default:
                    return nullptr;
                    break;
                }
            default:
                return nullptr;
                break;
            }
        }

        static std::shared_ptr<Message> CreateMessageServerbound(const int id, const ConnectionState state)
        {
            switch (state)
            {
            case ConnectionState::None:
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Handshake:
                switch (id)
                {
                case 0x00:
                    return std::shared_ptr<Handshake>(new Handshake);
                    break;
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Status:
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Login:
                switch (id)
                {
                case 0x00:
                    return std::shared_ptr<LoginStart>(new LoginStart);
                    break;
                case 0x01:
                    return std::shared_ptr<EncryptionResponse>(new EncryptionResponse);
                    break;
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Play:
                switch (id)
                {
#if PROTOCOL_VERSION == 340 // 1.12.2
                case 0x00:
                    return std::shared_ptr<TeleportConfirm>(new TeleportConfirm);
                    break;
                case 0x02:
                    return std::shared_ptr<ChatMessageServerbound>(new ChatMessageServerbound);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientStatus>(new ClientStatus);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientSettings>(new ClientSettings);
                    break;
                case 0x05:
                    return std::shared_ptr<ConfirmTransactionServerbound>(new ConfirmTransactionServerbound);
                    break;
                case 0x0B:
                    return std::shared_ptr<KeepAliveServerbound>(new KeepAliveServerbound);
                    break;
                case 0x0E:
                    return std::shared_ptr<PlayerPositionAndLookServerbound>(new PlayerPositionAndLookServerbound);
                    break;
                case 0x14:
                    return std::shared_ptr<PlayerDigging>(new PlayerDigging);
                    break;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
                case 0x00:
                    return std::shared_ptr<TeleportConfirm>(new TeleportConfirm);
                    break;
                case 0x02:
                    return std::shared_ptr<ChatMessageServerbound>(new ChatMessageServerbound);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientStatus>(new ClientStatus);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientSettings>(new ClientSettings);
                    break;
                case 0x06:
                    return std::shared_ptr<ConfirmTransactionServerbound>(new ConfirmTransactionServerbound);
                    break;
                case 0x0E:
                    return std::shared_ptr<KeepAliveServerbound>(new KeepAliveServerbound);
                    break;
                case 0x11:
                    return std::shared_ptr<PlayerPositionAndLookServerbound>(new PlayerPositionAndLookServerbound);
                    break;
                case 0x18:
                    return std::shared_ptr<PlayerDigging>(new PlayerDigging);
                    break;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
                case 0x00:
                    return std::shared_ptr<TeleportConfirm>(new TeleportConfirm);
                    break;
                case 0x03:
                    return std::shared_ptr<ChatMessageServerbound>(new ChatMessageServerbound);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientStatus>(new ClientStatus);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientSettings>(new ClientSettings);
                    break;
                case 0x07:
                    return std::shared_ptr<ConfirmTransactionServerbound>(new ConfirmTransactionServerbound);
                    break;
                case 0x0F:
                    return std::shared_ptr<KeepAliveServerbound>(new KeepAliveServerbound);
                    break;
                case 0x12:
                    return std::shared_ptr<PlayerPositionAndLookServerbound>(new PlayerPositionAndLookServerbound);
                    break;
                case 0x1A:
                    return std::shared_ptr<PlayerDigging>(new PlayerDigging);
                    break;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
                case 0x00:
                    return std::shared_ptr<TeleportConfirm>(new TeleportConfirm);
                    break;
                case 0x03:
                    return std::shared_ptr<ChatMessageServerbound>(new ChatMessageServerbound);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientStatus>(new ClientStatus);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientSettings>(new ClientSettings);
                    break;
                case 0x07:
                    return std::shared_ptr<ConfirmTransactionServerbound>(new ConfirmTransactionServerbound);
                    break;
                case 0x0F:
                    return std::shared_ptr<KeepAliveServerbound>(new KeepAliveServerbound);
                    break;
                case 0x12:
                    return std::shared_ptr<PlayerPositionAndLookServerbound>(new PlayerPositionAndLookServerbound);
                    break;
                case 0x1A:
                    return std::shared_ptr<PlayerDigging>(new PlayerDigging);
                    break;
#else
#error "Protocol version not implemented"
#endif
                default:
                    return nullptr;
                    break;
                }
            default:
                return nullptr;
                break;
            }
        }
    };
} //ProtocolCraft