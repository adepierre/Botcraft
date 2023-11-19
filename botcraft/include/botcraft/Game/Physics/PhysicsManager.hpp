#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>

#include "botcraft/Game/Vector3.hpp"

#include "protocolCraft/Handler.hpp"

namespace Botcraft
{
    class InventoryManager;
    class LocalPlayer;
    class NetworkManager;
    class World;
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
            const std::shared_ptr<LocalPlayer>& local_player_,
            const std::shared_ptr<NetworkManager>& network_manager_,
            const std::shared_ptr<World>& world_
        );
        ~PhysicsManager();

        void StartPhysics();
        void StopPhysics();

    protected:
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket& msg) override;

    private:
        void Physics();

        void SendPosition();

    private:
        struct PhysicsState
        {
            Vector3<double> position = Vector3<double>(0.0);
            Vector3<double> speed = Vector3<double>(0.0);
            float yaw = 0.0f;
            float pitch = 0.0f;
            bool has_physics = true;
            bool has_gravity = true;
            bool on_ground = false;
            bool in_water = false;
            bool under_water = false;
            bool in_lava = false;
            bool horizontal_collision = false;
            bool minor_horizontal_collision = false;
            bool vertical_collision = false;
            /// @brief Flying in creative/spectator mode
            bool flying = false;
            /// @brief Flying with elytra
            bool fall_flying = false;
            bool sprinting = false;
            bool crouching = false;
            bool swimming = false;

            float inputs_forward = 0.0f;
            float inputs_left = 0.0f;
            bool inputs_jump = false;
            bool inputs_sneak = false;
        };

#if USE_GUI
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif
        std::shared_ptr<InventoryManager> inventory_manager;
        std::shared_ptr<LocalPlayer> local_player;
        std::shared_ptr<NetworkManager> network_manager;
        std::shared_ptr<World> world;

        std::atomic<bool> should_run;
        std::atomic<bool> allow_flying;
        std::atomic<GameType> game_mode;

        PhysicsState current_state;
        PhysicsState previous_state;

        int ticks_since_last_position_sent;

        std::thread thread_physics; // Thread running to compute position and send it to the server every 50 ms (20 ticks/s)
    };
} // Botcraft
