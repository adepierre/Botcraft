#pragma once

#include <atomic>
#include <map>
#include <shared_mutex>
#include <thread>

#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/ConnectionClient.hpp"

namespace Botcraft
{
    class World;
    class InventoryManager;
    class EntityManager;
    class LocalPlayer;
    class PhysicsManager;

#if USE_GUI
    namespace Renderer
    {
        class RenderingManager;
    }
#endif

    /// @brief A client containing the different managers,
    /// and performing client-side physics.
    /// Can be inherited if you want to handle other packets
    /// without a need of any behaviour tree stuff.
    class ManagersClient : public ConnectionClient
    {
    public:
        ManagersClient(const bool use_renderer_);
        virtual ~ManagersClient();

        virtual void Disconnect() override;

        void SetSharedWorld(const std::shared_ptr<World> world_);

        bool GetAutoRespawn() const;
        void SetAutoRespawn(const bool b);

        // Set the right transaction id, add it to the inventory manager,
        // update the next transaction id and send it to the server
        // return the id of the transaction
        int SendInventoryTransaction(const std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket>& transaction);

        std::shared_ptr<World> GetWorld() const;
        std::shared_ptr<EntityManager> GetEntityManager() const;
        std::shared_ptr<LocalPlayer> GetLocalPlayer() const;
        std::shared_ptr<InventoryManager> GetInventoryManager() const;
        std::shared_ptr<PhysicsManager> GetPhysicsManager() const;

        /// @brief Get the name of a connected player
        /// @param uuid UUID of the player
        /// @return The name, or empty string if not present
        std::string GetPlayerName(const ProtocolCraft::UUID& uuid) const;


        /// @brief Get the current tick
        /// @return An int representing the time of day
        int GetDayTime() const;

    protected:
        using ConnectionClient::Handle; // Don't hide all Handle() functions from base classes
        virtual void Handle(ProtocolCraft::ClientboundGameProfilePacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundChangeDifficultyPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetTimePacket& msg) override;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        virtual void Handle(ProtocolCraft::ClientboundPlayerInfoPacket& msg) override;
#else
        virtual void Handle(ProtocolCraft::ClientboundPlayerInfoRemovePacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerInfoUpdatePacket& msg) override;
#endif

    protected:
        std::shared_ptr<World> world;
        std::shared_ptr<EntityManager> entity_manager;
        std::shared_ptr<InventoryManager> inventory_manager;
        std::shared_ptr<PhysicsManager> physics_manager;
#if USE_GUI
        // If true, opens a window to display the view
        // from the bot. Only one renderer can be active
        // at the same time
        bool use_renderer;
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif

        bool auto_respawn;

        Difficulty difficulty;
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
        bool difficulty_locked;
#endif
        bool is_hardcore;
        std::atomic<int> day_time;

        /// @brief Names of all connected players
        std::map<ProtocolCraft::UUID, std::string> player_names;
        mutable std::shared_mutex player_names_mutex;
    };
} //Botcraft
