#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>

#include "botcraft/Game/Vector3.hpp"

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

    class PhysicsManager// : public ProtocolCraft::Handler // There is no physics related packets yet
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
        void ApplyInputs(const double strength) const;
        /// @brief Send position/rotation/on_ground to server
        void SendPosition();

        /// @brief Check collisions between an AABB and a list of colliders
        /// @param movement Movement vector to apply to AABB, will be changed based on collisions
        /// @param aabb AABB to move, will be translated based on movement and colliders
        void Collisions(Vector3<double>& movement, AABB& aabb) const;

        bool IsSwimmingAndNotFlying() const;
        bool IsInClimbable() const;
        void MovePlayer() const;
        void ApplyMovement() const;

        void OnUpdateAbilities() const;
        void CheckInsideBlocks() const;

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

        int ticks_since_last_position_sent;

        std::thread thread_physics; // Thread running to compute position and send it to the server every 50 ms (20 ticks/s)

        const Item* elytra_item;
    };
} // Botcraft
