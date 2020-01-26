#pragma once

#include <memory>

#include "botcraft/Protocol/AllMessages.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class MessageFactory
    {
    public:
        static std::shared_ptr<Message> CreateMessage(const int id, const int state)
        {
            switch (state)
            {
            case -1: // None
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case 0: // Handshaking
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case 1: // Status
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case 2: // Login
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
            case 3: // Play
                switch (id)
                {
#if PROTOCOL_VERSION == 340 // 1.12.2
				case 0x09:
					return std::shared_ptr<UpdateBlockEntity>(new UpdateBlockEntity);
				break; 
				case 0x0B:
                    return std::shared_ptr<BlockChange>(new BlockChange);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerDifficulty>(new ServerDifficulty);
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
                case 0x13:
                    return std::shared_ptr<OpenWindow>(new OpenWindow);
                    break;
                case 0x14:
                    return std::shared_ptr<WindowItems>(new WindowItems);
                    break;
                case 0x16:
                    return std::shared_ptr<SetSlot>(new SetSlot);
                    break;
                case 0x1A:
                    return std::shared_ptr<DisconnectPlay>(new DisconnectPlay);
                    break;
                case 0x1D:
                    return std::shared_ptr<UnloadChunk>(new UnloadChunk);
                    break;
                case 0x1F:
                    return std::shared_ptr<KeepAliveClientbound>(new KeepAliveClientbound);
                    break;
                case 0x20:
                    return std::shared_ptr<ChunkData>(new ChunkData);
                    break;
                case 0x23:
                    return std::shared_ptr<JoinGame>(new JoinGame);
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
                case 0x2C:
                    return std::shared_ptr<PlayerAbilitiesClientbound>(new PlayerAbilitiesClientbound);
                    break;
                case 0x2E:
                    return std::shared_ptr<PlayerInfo>(new PlayerInfo);
                    break;
                case 0x2F:
                    return std::shared_ptr<PlayerPositionAndLookClientbound>(new PlayerPositionAndLookClientbound);
                    break;
                case 0x35:
                    return std::shared_ptr<Respawn>(new Respawn);
                    break;
                case 0x3A:
                    return std::shared_ptr<HeldItemChangeClientbound>(new HeldItemChangeClientbound);
                    break;
                case 0x41:
                    return std::shared_ptr<UpdateHealth>(new UpdateHealth);
                    break;
                case 0x47:
                    return std::shared_ptr<TimeUpdate>(new TimeUpdate);
                    break;
                case 0x4C:
                    return std::shared_ptr<EntityTeleport>(new EntityTeleport);
                    break;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
				case 0x09:
					return std::shared_ptr<UpdateBlockEntity>(new UpdateBlockEntity);
					break;
				case 0x0B:
                    return std::shared_ptr<BlockChange>(new BlockChange);
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
                case 0x12:
                    return std::shared_ptr<ConfirmTransactionClientbound>(new ConfirmTransactionClientbound);
                    break;
                case 0x14:
                    return std::shared_ptr<OpenWindow>(new OpenWindow);
                    break;
                case 0x15:
                    return std::shared_ptr<WindowItems>(new WindowItems);
                    break;
                case 0x17:
                    return std::shared_ptr<SetSlot>(new SetSlot);
                    break;
                case 0x1B:
                    return std::shared_ptr<DisconnectPlay>(new DisconnectPlay);
                    break;
                case 0x1F:
                    return std::shared_ptr<UnloadChunk>(new UnloadChunk);
                    break;
                case 0x21:
                    return std::shared_ptr<KeepAliveClientbound>(new KeepAliveClientbound);
                    break;
                case 0x22:
                    return std::shared_ptr<ChunkData>(new ChunkData);
                    break;
                case 0x25:
                    return std::shared_ptr<JoinGame>(new JoinGame);
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
                case 0x2E:
                    return std::shared_ptr<PlayerAbilitiesClientbound>(new PlayerAbilitiesClientbound);
                    break;
                case 0x30:
                    return std::shared_ptr<PlayerInfo>(new PlayerInfo);
                    break;
                case 0x32:
                    return std::shared_ptr<PlayerPositionAndLookClientbound>(new PlayerPositionAndLookClientbound);
                    break;
                case 0x38:
                    return std::shared_ptr<Respawn>(new Respawn);
                    break;
                case 0x3D:
                    return std::shared_ptr<HeldItemChangeClientbound>(new HeldItemChangeClientbound);
                    break;
                case 0x44:
                    return std::shared_ptr<UpdateHealth>(new UpdateHealth);
                    break;
                case 0x4A:
                    return std::shared_ptr<TimeUpdate>(new TimeUpdate);
                    break;
                case 0x50:
                    return std::shared_ptr<EntityTeleport>(new EntityTeleport);
                    break;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
				case 0x09:
					return std::shared_ptr<UpdateBlockEntity>(new UpdateBlockEntity);
				break; 
				case 0x0B:
                    return std::shared_ptr<BlockChange>(new BlockChange);
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
                case 0x12:
                    return std::shared_ptr<ConfirmTransactionClientbound>(new ConfirmTransactionClientbound);
                    break;
                case 0x13:
                    return std::shared_ptr<OpenWindow>(new OpenWindow);
                    break;
                case 0x14:
                    return std::shared_ptr<WindowItems>(new WindowItems);
                    break;
                case 0x16:
                    return std::shared_ptr<SetSlot>(new SetSlot);
                    break;
                case 0x1A:
                    return std::shared_ptr<DisconnectPlay>(new DisconnectPlay);
                    break;
                case 0x1D:
                    return std::shared_ptr<UnloadChunk>(new UnloadChunk);
                    break;
                case 0x20:
                    return std::shared_ptr<KeepAliveClientbound>(new KeepAliveClientbound);
                    break;
                case 0x21:
                    return std::shared_ptr<ChunkData>(new ChunkData);
                    break;
                case 0x24:
                    return std::shared_ptr<UpdateLight>(new UpdateLight);
                    break;
                case 0x25:
                    return std::shared_ptr<JoinGame>(new JoinGame);
                    break;
                case 0x2B:
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
                case 0x31:
                    return std::shared_ptr<PlayerAbilitiesClientbound>(new PlayerAbilitiesClientbound);
                    break;
                case 0x33:
                    return std::shared_ptr<PlayerInfo>(new PlayerInfo);
                    break;
                case 0x35:
                    return std::shared_ptr<PlayerPositionAndLookClientbound>(new PlayerPositionAndLookClientbound);
                    break;
                case 0x3A:
                    return std::shared_ptr<Respawn>(new Respawn);
                    break;
                case 0x3F:
                    return std::shared_ptr<HeldItemChangeClientbound>(new HeldItemChangeClientbound);
                    break;
                case 0x48:
                    return std::shared_ptr<UpdateHealth>(new UpdateHealth);
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
				case 0x08:
					return std::shared_ptr<AcknowledgePlayerDigging>(new AcknowledgePlayerDigging);
					break;
				case 0x0A:
					return std::shared_ptr<UpdateBlockEntity>(new UpdateBlockEntity);
					break;
				case 0x0C:
					return std::shared_ptr<BlockChange>(new BlockChange);
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
				case 0x13:
					return std::shared_ptr<ConfirmTransactionClientbound>(new ConfirmTransactionClientbound);
					break;
				case 0x14:
					return std::shared_ptr<OpenWindow>(new OpenWindow);
					break;
				case 0x15:
					return std::shared_ptr<WindowItems>(new WindowItems);
					break;
				case 0x17:
					return std::shared_ptr<SetSlot>(new SetSlot);
					break;
				case 0x1B:
					return std::shared_ptr<DisconnectPlay>(new DisconnectPlay);
					break;
				case 0x1E:
					return std::shared_ptr<UnloadChunk>(new UnloadChunk);
					break;
				case 0x21:
					return std::shared_ptr<KeepAliveClientbound>(new KeepAliveClientbound);
					break;
				case 0x22:
					return std::shared_ptr<ChunkData>(new ChunkData);
					break;
				case 0x25:
					return std::shared_ptr<UpdateLight>(new UpdateLight);
					break;
				case 0x26:
					return std::shared_ptr<JoinGame>(new JoinGame);
					break;
				case 0x2C:
					return std::shared_ptr<Entity>(new Entity);
					break;
				case 0x29:
					return std::shared_ptr<EntityRelativeMove>(new EntityRelativeMove);
					break;
				case 0x2A:
					return std::shared_ptr<EntityLookAndRelativeMove>(new EntityLookAndRelativeMove);
					break;
				case 0x2B:
					return std::shared_ptr<EntityLook>(new EntityLook);
					break;
				case 0x32:
					return std::shared_ptr<PlayerAbilitiesClientbound>(new PlayerAbilitiesClientbound);
					break;
				case 0x34:
					return std::shared_ptr<PlayerInfo>(new PlayerInfo);
					break;
				case 0x36:
					return std::shared_ptr<PlayerPositionAndLookClientbound>(new PlayerPositionAndLookClientbound);
					break;
				case 0x3B:
					return std::shared_ptr<Respawn>(new Respawn);
					break;
				case 0x40:
					return std::shared_ptr<HeldItemChangeClientbound>(new HeldItemChangeClientbound);
					break;
				case 0x49:
					return std::shared_ptr<UpdateHealth>(new UpdateHealth);
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
    };
} //Botcraft