#pragma once

#include <atomic>
#include <memory>
#include <optional>
#include <thread>

#include "protocolCraft/Handler.hpp"

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/Physics/AABB.hpp"

namespace Botcraft
{
    class EntityManager;
    class InventoryManager;
    class LocalPlayer;
    class NetworkManager;
    class World;

    class Item;

#if USE_GUI
    namespace Renderer
    {
        class RenderingManager;
    }
#endif

    class PhysicsManager : public ProtocolCraft::Handler
    {
    public:
        PhysicsManager() = delete;
        PhysicsManager(
#if USE_GUI
            const std::shared_ptr<Renderer::RenderingManager>& rendering_manager_,
#endif
            const std::shared_ptr<InventoryManager>& inventory_manager_,
            const std::shared_ptr<EntityManager>& entity_manager_,
            const std::shared_ptr<NetworkManager>& network_manager_,
            const std::shared_ptr<World>& world_
        );
        ~PhysicsManager();

        void StartPhysics();
        void StopPhysics();

        double GetMsPerTick() const;

    protected:
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerPositionPacket& msg) override;
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        virtual void Handle(ProtocolCraft::ClientboundTickingStatePacket& msg) override;
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        virtual void Handle(ProtocolCraft::ClientboundPlayerRotationPacket& msg) override;
#endif

    private:
        void Physics();

        /// @brief Follow minecraft physics related flow in LocalPlayer tick function
        void PhysicsTick();
        void UpdateSwimming() const;
        /// @brief Perform fluid physics on the player, and set in_water/lava boolean accordingly
        /// @param water If true, will push with water, lava otherwise
        void FluidPhysics(const bool water);
        void InputsToCrouch() const;
        void InputsToSprint() const;
        void SetSprinting(const bool b) const;
        void InputsToFly() const;
        void InputsToJump() const;
        void ApplyInputs(const float strength) const;
        /// @brief Send position/rotation/on_ground to server
        void SendPosition();

        /// @brief Check collisions of an AABB with a given movement
        /// @param aabb AABB to move
        /// @param movement Movement vector to apply to AABB
        /// @return New movement vector after collisions
        Vector3<double> CollideBoundingBox(const AABB& aabb, const Vector3<double>& movement) const;

        void CollideOneAxis(AABB& aabb, Vector3<double>& movement, const unsigned int axis, const std::vector<AABB>& colliders) const;

        bool IsSwimmingAndNotFlying() const;
        bool IsInClimbable() const;
        void MovePlayer() const;
        void ApplyMovement() const;

        void OnUpdateAbilities() const;
        void CheckInsideBlocks() const;
        Position GetBlockBelowAffectingMovement() const;

    private:
#if USE_GUI
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif
        std::shared_ptr<EntityManager> entity_manager;
        std::shared_ptr<InventoryManager> inventory_manager;
        std::shared_ptr<LocalPlayer> player;
        std::shared_ptr<NetworkManager> network_manager;
        std::shared_ptr<World> world;

        std::atomic<bool> should_run;
        std::optional<int> teleport_id;

        int ticks_since_last_position_sent;

        std::thread thread_physics; // Thread running to compute position and send it to the server every tick

        const Item* elytra_item;

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        std::atomic<double> ms_per_tick = 50.0;
#else
        static constexpr double ms_per_tick = 50.0;
#endif

    };
} // Botcraft
