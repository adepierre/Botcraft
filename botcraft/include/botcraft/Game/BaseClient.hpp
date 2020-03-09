#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <unordered_set>

#include "protocolCraft/Handler.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllMessages.hpp"
#include "botcraft/Game/Player.hpp"
#include "botcraft/Game/Enums.hpp"

#if USE_GUI
#include "botcraft/Renderer/CubeWorldRenderer.hpp"
#endif

namespace ProtocolCraft
{
    class Handler : public GenericHandler<Message, AllMessages> {};
}

namespace Botcraft
{
    class World;
    class TCP_Com;
    class InventoryManager;
    class Authentifier;


    class BaseClient : public ProtocolCraft::Handler
    {
    public:
        BaseClient(const bool afk_only_ = false, const std::vector<int> &printed_packets_ = std::vector<int>(0));
        ~BaseClient();

        // Connect to a server, if password is empty, the server must be in offline mode
        void Connect(const std::string &ip, const unsigned int port, const std::string &login, const std::string &password);
        void Disconnect();

    protected:
        void Send(const std::shared_ptr<ProtocolCraft::Message> msg);
        void WaitForNewPackets();
        void OnNewPacket(const std::vector<unsigned char> &packet);
        void ProcessPacket(const std::vector<unsigned char> &packet);

        void RunSyncPos();
        void Physics();

#ifdef USE_GUI
        void AddChunkToUpdate(const int x, const int z);
        void WaitForRenderingUpdate();
#endif

    protected:
        virtual void Handle(ProtocolCraft::Message &msg) override;
        virtual void Handle(ProtocolCraft::DisconnectLogin &msg) override;
        virtual void Handle(ProtocolCraft::LoginSuccess &msg) override;
        virtual void Handle(ProtocolCraft::SetCompression &msg) override;
        virtual void Handle(ProtocolCraft::BlockChange &msg) override;
        virtual void Handle(ProtocolCraft::ServerDifficulty &msg) override;
        virtual void Handle(ProtocolCraft::MultiBlockChange &msg) override;
        virtual void Handle(ProtocolCraft::ConfirmTransactionClientbound &msg) override;
        virtual void Handle(ProtocolCraft::DisconnectPlay &msg) override;
        virtual void Handle(ProtocolCraft::UnloadChunk &msg) override;
        virtual void Handle(ProtocolCraft::KeepAliveClientbound &msg) override;
        virtual void Handle(ProtocolCraft::ChunkData &msg) override;
        virtual void Handle(ProtocolCraft::JoinGame &msg) override;
        virtual void Handle(ProtocolCraft::Entity &msg) override;
        virtual void Handle(ProtocolCraft::EntityRelativeMove &msg) override;
        virtual void Handle(ProtocolCraft::EntityLookAndRelativeMove &msg) override;
        virtual void Handle(ProtocolCraft::EntityLook &msg) override;
        virtual void Handle(ProtocolCraft::PlayerPositionAndLookClientbound &msg) override;
        virtual void Handle(ProtocolCraft::UpdateHealth &msg) override;
        virtual void Handle(ProtocolCraft::EntityTeleport &msg) override;
        virtual void Handle(ProtocolCraft::PlayerAbilitiesClientbound &msg) override;
        virtual void Handle(ProtocolCraft::TimeUpdate &msg) override;
        virtual void Handle(ProtocolCraft::EncryptionRequest &msg) override;
        virtual void Handle(ProtocolCraft::Respawn &msg) override;
#if PROTOCOL_VERSION > 404
        virtual void Handle(ProtocolCraft::UpdateLight &msg) override;
#endif
        virtual void Handle(ProtocolCraft::UpdateBlockEntity &msg) override;
        virtual void Handle(ProtocolCraft::PlayerInfo &msg) override;
        virtual void Handle(ProtocolCraft::SetSlot &msg) override;
        virtual void Handle(ProtocolCraft::WindowItems &msg) override;
        virtual void Handle(ProtocolCraft::OpenWindow &msg) override;
        virtual void Handle(ProtocolCraft::HeldItemChangeClientbound &msg) override;

    protected:
        // If in afk only mode, the chunks will NOT
        // be stored in memory and physics will NOT
        // be calculated
        // Use it only to afk at a specific spot
        bool afk_only;

        std::shared_ptr<TCP_Com> com;
        std::shared_ptr<Authentifier> authentifier;
        std::shared_ptr<World> world;
        std::mutex world_mutex;
        std::shared_ptr<Player> player;
        std::mutex player_mutex;
        std::shared_ptr<InventoryManager> inventory_manager;
        std::mutex inventory_manager_mutex;

#if USE_GUI
        std::shared_ptr<Renderer::CubeWorldRenderer> renderer;

        std::unordered_set<Position> chunks_to_render;
        std::mutex mutex_rendering;
        std::condition_variable condition_rendering;
        
        std::thread m_thread_update_renderer;// Thread used to update the renderer with world data 
#endif

        bool auto_respawn;

        State state;
        GameMode game_mode;
        Dimension dimension;
        Difficulty difficulty;
#if PROTOCOL_VERSION > 463
        bool difficulty_locked;
#endif
        bool is_hardcore;

        bool allow_flying;
        bool creative_mode; // Instant break

        std::thread m_thread_physics;//Thread running to compute position and send it to the server every 50 ms (20 ticks/s)
        std::thread m_thread_process;//Thread running to process incoming packets without blocking com

        std::deque<std::vector<unsigned char> > packets_to_process;
        std::mutex mutex_process;
        std::condition_variable process_condition;

        std::vector<bool> printed_packets;

        bool should_be_closed;

        int compression;

        std::string name;
    };
} //Botcraft