#pragma once

#include <thread>
#include <atomic>
#include <memory>

namespace Botcraft
{
    class EntityManager;
    class World;
    class NetworkManager;
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
            const std::shared_ptr<EntityManager>& entity_manager_,
            const std::shared_ptr<World>& world_,
            const std::shared_ptr<NetworkManager>& network_manager_     
        );
        ~PhysicsManager();

        void StartPhysics();
        void StopPhysics();
        void SetShouldFallInVoid(const bool b);

    private:
        void RunSyncPos();
        void Physics();
        void UpdatePlayerSpeed() const;

    private:
#if USE_GUI
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif
        std::shared_ptr<EntityManager> entity_manager;
        std::shared_ptr<World> world;
        std::shared_ptr<NetworkManager> network_manager;

        std::atomic<bool> should_run;

        bool should_fall_in_void;

        std::thread thread_physics;//Thread running to compute position and send it to the server every 50 ms (20 ticks/s)
    };
} // Botcraft