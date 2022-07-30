#pragma once

#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <mutex>
#include <functional>
#include <array>
#include <vector>
#include <memory>
#include <map>
#include <thread>
#include <condition_variable>
#include <deque>
#include <fstream>

#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Renderer/Face.hpp"

#include "protocolCraft/Handler.hpp"

struct GLFWwindow;

namespace Botcraft
{
    class World;
    class InventoryManager;
    class EntityManager;

    namespace Renderer
    {
        class Shader;
        class Atlas;
        class WorldRenderer;

        // Key that can be used in KeyboardCallback when set
        enum class KEY_CODE
        {
            FORWARD = 0,
            BACKWARD,
            RIGHT,
            LEFT,
            SPACE,
            SHIFT,
            CTRL,
            ESC,
            MOUSE_LEFT,
            INVENTORY,
            NUMBER_OF_KEYS
        };

        class RenderingManager : public ProtocolCraft::Handler
        {
        public:
            // Constructor
            // Window can be resized at runtime
            // Chunks in renderer are independant of chunks in the corresponding world.
            // Set headless_ to true to run without opening a window (rendering is still done)
            RenderingManager(std::shared_ptr<World> world_, std::shared_ptr<InventoryManager> inventory_manager_,
                std::shared_ptr<EntityManager> entity_manager_,
                const unsigned int &window_width, const unsigned int &window_height,
                const unsigned int section_height_ = 16, const bool headless = false);
            ~RenderingManager();

            // Set a flag to terminate the rendering loop after the current frame
            void Close();

            // Set mouse and keyboard callbacks to handle user inputs
            void SetMouseCallback(std::function<void(double, double)> callback);
            void SetKeyboardCallback(std::function<void(std::array<bool, static_cast<int>(KEY_CODE::NUMBER_OF_KEYS)>, double)> callback);
            void AddChunkToUpdate(const int x, const int z);
            void AddEntityToUpdate(const int id);

            // Set world renderer's camera position and orientation
            void SetPosOrientation(const double x_, const double y_, const double z_, const float yaw_, const float pitch_);

            // Take a screenshot of the current frame and save it to path
            void Screenshot(const std::string &path);

        protected:
            void WaitForRenderingUpdate();

            virtual void Handle(ProtocolCraft::Message& msg) override;
            
            // Chunk stuff
            virtual void Handle(ProtocolCraft::ClientboundBlockUpdatePacket& msg) override;
            virtual void Handle(ProtocolCraft::ClientboundSectionBlocksUpdatePacket& msg) override;
            virtual void Handle(ProtocolCraft::ClientboundForgetLevelChunkPacket& msg) override;
#if PROTOCOL_VERSION < 757
            virtual void Handle(ProtocolCraft::ClientboundLevelChunkPacket& msg) override;
#else
            virtual void Handle(ProtocolCraft::ClientboundLevelChunkWithLightPacket& msg) override;
#endif

            // Entity stuff
            virtual void Handle(ProtocolCraft::ClientboundAddEntityPacket& msg) override;
#if PROTOCOL_VERSION < 759
            virtual void Handle(ProtocolCraft::ClientboundAddMobPacket& msg) override;
#endif
#if PROTOCOL_VERSION < 721
            virtual void Handle(ProtocolCraft::ClientboundAddGlobalEntityPacket& msg) override;
#endif
            virtual void Handle(ProtocolCraft::ClientboundAddPlayerPacket& msg) override;
            virtual void Handle(ProtocolCraft::ClientboundTeleportEntityPacket& msg) override;
#if PROTOCOL_VERSION < 755
            virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacket& msg) override;
#endif
            virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& msg) override;
            virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& msg) override;
            virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& msg) override;
#if PROTOCOL_VERSION == 755
            virtual void Handle(ProtocolCraft::ClientboundRemoveEntityPacket& msg) override;
#else
            virtual void Handle(ProtocolCraft::ClientboundRemoveEntitiesPacket& msg) override;
#endif

            // Misc stuff
            virtual void Handle(ProtocolCraft::ClientboundSetTimePacket& msg) override;
            virtual void Handle(ProtocolCraft::ClientboundRespawnPacket& msg) override;



        private:
            // Initialize all the stuff
            bool Init(const bool headless);

            // Main rendering loop
            void Run(const bool headless);

            // Callbacks called by glfw
            static void ResizeCallback(GLFWwindow* window, int width, int height);
            static void InternalMouseCallback(GLFWwindow *window, double xpos, double ypos);

            // Get GLFW keyboard inputs and pass them to the callback
            void InternalProcessInput(GLFWwindow *window);

        private:
            // External modules
            std::shared_ptr<World> world;
            std::shared_ptr<InventoryManager> inventory_manager;
            std::shared_ptr<EntityManager> entity_manager;

            std::array<bool, static_cast<int>(KEY_CODE::NUMBER_OF_KEYS)> isKeyPressed;

#if USE_IMGUI
            bool inventory_open;
#endif

            std::thread rendering_thread;// OpenGL thread
            
            double mouse_last_x;
            double mouse_last_y;
            bool first_mouse;

            double deltaTime;
            double lastFrameTime;

            GLFWwindow *window;
            int current_window_width;
            int current_window_height;
            bool has_proj_changed;

            // 0.5 is noon, 0 and 1 are midnight
            float day_time;

            std::unique_ptr<Shader> my_shader;

            std::unique_ptr<WorldRenderer> world_renderer;

            std::function<void(double, double)> MouseCallback;
            std::function<void(std::array<bool, static_cast<int>(KEY_CODE::NUMBER_OF_KEYS)>, double)> KeyboardCallback;

            std::string screenshot_path;
            bool take_screenshot;

            bool running;

            std::unordered_set<Position> chunks_to_udpate;
            std::unordered_set<int> entities_to_update;
            std::mutex mutex_updating;
            std::condition_variable condition_update;
            // Thread used to update the rendered data with current data 
            std::thread thread_updating_renderable; 
        };
    } // Renderer
} // Botcraft