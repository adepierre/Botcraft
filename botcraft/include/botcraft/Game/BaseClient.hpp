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

namespace Botcraft
{
    class World;
    class InventoryManager;
    class NetworkManager;

#if USE_GUI
    namespace Renderer
    {
        class RenderingManager;
    }
#endif

    class BaseClient : public ProtocolCraft::Handler
    {
    public:
        BaseClient(const bool use_renderer_, const bool afk_only_ = false);
        ~BaseClient();

        // Connect to a server, if password is empty, the server must be in offline mode
        void Connect(const std::string &address, const std::string &login, const std::string &password);
        void Disconnect();

        void SetSharedWorld(const std::shared_ptr<World> world_);

    protected:
        void RunSyncPos();
        void Physics();

    protected:
        virtual void Handle(ProtocolCraft::Message &msg) override;
        virtual void Handle(ProtocolCraft::DisconnectLogin &msg) override;
        virtual void Handle(ProtocolCraft::LoginSuccess &msg) override;
        virtual void Handle(ProtocolCraft::ServerDifficulty &msg) override;
        virtual void Handle(ProtocolCraft::ConfirmTransactionClientbound &msg) override;
        virtual void Handle(ProtocolCraft::DisconnectPlay &msg) override;
        virtual void Handle(ProtocolCraft::JoinGame &msg) override;
        virtual void Handle(ProtocolCraft::Entity &msg) override;
        virtual void Handle(ProtocolCraft::EntityRelativeMove &msg) override;
        virtual void Handle(ProtocolCraft::EntityLookAndRelativeMove &msg) override;
        virtual void Handle(ProtocolCraft::EntityLook &msg) override;
        virtual void Handle(ProtocolCraft::PlayerPositionAndLookClientbound &msg) override;
        virtual void Handle(ProtocolCraft::UpdateHealth &msg) override;
        virtual void Handle(ProtocolCraft::EntityTeleport &msg) override;
        virtual void Handle(ProtocolCraft::PlayerAbilitiesClientbound &msg) override;
        virtual void Handle(ProtocolCraft::Respawn &msg) override;

    protected:
        // If in afk only mode, the chunks will NOT
        // be stored in memory and physics will NOT
        // be calculated
        // Use it only to afk at a specific spot
        bool afk_only;

        // If true, opens a window to display the view
        // from the bot. Only one renderer can be active
        // at the same time
#if USE_GUI
        bool use_renderer;
#endif

        std::shared_ptr<World> world;
        std::shared_ptr<Player> player;
        std::shared_ptr<InventoryManager> inventory_manager;
        std::shared_ptr<NetworkManager> network_manager;
#if USE_GUI
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif

        bool auto_respawn;

        //ProtocolCraft::ConnectionState state;
        GameMode game_mode;

        Difficulty difficulty;
#if PROTOCOL_VERSION > 463
        bool difficulty_locked;
#endif
        bool is_hardcore;

        bool allow_flying;
        bool creative_mode; // Instant break

        std::thread m_thread_physics;//Thread running to compute position and send it to the server every 50 ms (20 ticks/s)

        bool should_be_closed;
    };
} //Botcraft