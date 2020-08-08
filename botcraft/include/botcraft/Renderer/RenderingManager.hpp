#pragma once

#include "protocolCraft/Handler.hpp"

#include "botcraft/Game/Vector3.hpp"

#include <unordered_set>
#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>

namespace Botcraft
{
    class World;

    namespace Renderer
    {
        class CubeWorldRenderer;

        class RenderingManager : public ProtocolCraft::Handler
        {
        public:
            RenderingManager(std::shared_ptr<World> world_);
            ~RenderingManager();

            std::shared_ptr<CubeWorldRenderer> GetRenderer();
            void AddChunkToUpdate(const int x, const int z);

        protected:
            void WaitForRenderingUpdate();

            virtual void Handle(ProtocolCraft::Message& msg) override;
            virtual void Handle(ProtocolCraft::BlockChange& msg) override;
            virtual void Handle(ProtocolCraft::MultiBlockChange& msg) override;
            virtual void Handle(ProtocolCraft::UnloadChunk& msg) override;
            virtual void Handle(ProtocolCraft::ChunkData& msg) override;
            virtual void Handle(ProtocolCraft::TimeUpdate& msg) override;
            virtual void Handle(ProtocolCraft::Respawn& msg) override;

        private:
            bool running;
            std::shared_ptr<World> world;
            std::shared_ptr<CubeWorldRenderer> renderer;

            std::unordered_set<Position> chunks_to_render;
            std::mutex mutex_rendering;
            std::condition_variable condition_rendering;

            std::thread m_thread_update_renderer;// Thread used to update the renderer with world data 
        };
    } // Renderer
} // Botcraft