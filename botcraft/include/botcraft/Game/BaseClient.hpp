#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <unordered_set>

#include "protocolCraft/Handler.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllMessages.hpp"
#include "botcraft/Game/Enums.hpp"

namespace Botcraft
{
    class World;
    class InventoryManager;
    class NetworkManager;
    class EntityManager;

#if USE_GUI
    namespace Renderer
    {
        class RenderingManager;
    }
#endif

    /// <summary>
    /// The base class containing the different managers.
    /// You can inherit it to handle other packets if you 
    /// only need some low-level stuff without more complex 
    /// bot behaviours.
    /// </summary>
    class BaseClient : public ProtocolCraft::Handler
    {
    public:
        BaseClient(const bool use_renderer_, const bool afk_only_ = false);
        virtual ~BaseClient();

        // Connect to a server, if password is empty, the server must be in offline mode
        // If login and password are empty, use microsoft account auth
        void Connect(const std::string& address, const std::string& login, const std::string& password);
        void Disconnect();

        void SetSharedWorld(const std::shared_ptr<World> world_);

        const bool GetShouldBeClosed() const;


        // Send a message in the chat
        void SendChatMessage(const std::string& msg);
        // Ask to respawn when dead (use it if auto_respawn is false)
        void Respawn();
        void SetAutoRespawn(const bool b);


        // Set the right transaction id, add it to the inventory manager,
        // update the next transaction id and send it to the server
        // return the id of the transaction
        const int SendInventoryTransaction(std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket> transaction);

        std::shared_ptr<World> GetWorld() const;
        std::shared_ptr<EntityManager> GetEntityManager() const;
        std::shared_ptr<NetworkManager> GetNetworkManager() const;
        std::shared_ptr<InventoryManager> GetInventoryManager() const;
        const bool GetCreativeMode() const;


    protected:
        void RunSyncPos();
        void Physics(const bool is_in_fluid);

    protected:
        virtual void Handle(ProtocolCraft::Message &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundLoginDisconnectPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundGameProfilePacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundChangeDifficultyPacket &msg) override;
#if PROTOCOL_VERSION < 755
        virtual void Handle(ProtocolCraft::ClientboundContainerAckPacket &msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundDisconnectPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerPositionPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket &msg) override;

    protected:
        // If in afk only mode, the chunks will NOT
        // be stored in memory and physics will NOT
        // be calculated
        // Use it only to afk at a specific spot with
        // very low CPU/RAM usage
        bool afk_only;

        std::shared_ptr<World> world;
        std::shared_ptr<EntityManager> entity_manager;
        std::shared_ptr<InventoryManager> inventory_manager;
        std::shared_ptr<NetworkManager> network_manager;
#if USE_GUI
        // If true, opens a window to display the view
        // from the bot. Only one renderer can be active
        // at the same time
        bool use_renderer;
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif

        bool auto_respawn;

        //ProtocolCraft::ConnectionState state;
        GameType game_mode;

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