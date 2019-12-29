#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <unordered_set>

#include "botcraft/Protocol/Handler.hpp"
#include "botcraft/Protocol/Message.hpp"
#include "botcraft/Protocol/AllMessages.hpp"
#include "botcraft/Game/Player.hpp"
#include "botcraft/Game/Enums.hpp"

#include "botcraft/Version.hpp"

#if USE_GUI
#include "botcraft/Renderer/CubeWorldRenderer.hpp"
#endif

namespace Botcraft
{
    class World;
    class TCP_Com;
    class InventoryManager;

    class Handler : public GenericHandler<Message, AllMessages> {};

    class BaseClient : public Handler
    {
    public:
        BaseClient(const std::vector<int> &printed_packets_ = std::vector<int>(0));
        ~BaseClient();

        // Connect to a server
        void Connect(const std::string &ip, const unsigned int port, const std::string &player_name);
        void Disconnect();

    protected:
        void Send(const std::shared_ptr<Message> msg);
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
        virtual void Handle(Message &msg) override;
        virtual void Handle(DisconnectLogin &msg) override;
        virtual void Handle(LoginSuccess &msg) override;
        virtual void Handle(SetCompression &msg) override;
        virtual void Handle(BlockChange &msg) override;
        virtual void Handle(ServerDifficulty &msg) override;
        virtual void Handle(MultiBlockChange &msg) override;
        virtual void Handle(ConfirmTransactionClientbound &msg) override;
        virtual void Handle(DisconnectPlay &msg) override;
        virtual void Handle(UnloadChunk &msg) override;
        virtual void Handle(KeepAliveClientbound &msg) override;
        virtual void Handle(ChunkData &msg) override;
        virtual void Handle(JoinGame &msg) override;
        virtual void Handle(Entity &msg) override;
        virtual void Handle(EntityRelativeMove &msg) override;
        virtual void Handle(EntityLookAndRelativeMove &msg) override;
        virtual void Handle(EntityLook &msg) override;
        virtual void Handle(PlayerPositionAndLookClientbound &msg) override;
        virtual void Handle(UpdateHealth &msg) override;
        virtual void Handle(EntityTeleport &msg) override;
        virtual void Handle(PlayerAbilitiesClientbound &msg) override;
        virtual void Handle(TimeUpdate &msg) override;
        virtual void Handle(EncryptionRequest &msg) override;
        virtual void Handle(Respawn &msg) override;
#if PROTOCOL_VERSION > 404
        virtual void Handle(UpdateLight &msg) override;
#endif
        virtual void Handle(UpdateBlockEntity &msg) override;
        virtual void Handle(PlayerInfo &msg) override;
        virtual void Handle(SetSlot &msg) override;
        virtual void Handle(WindowItems &msg) override;
        virtual void Handle(OpenWindow &msg) override;
        virtual void Handle(HeldItemChangeClientbound &msg) override;

    protected:
        std::shared_ptr<TCP_Com> com;
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