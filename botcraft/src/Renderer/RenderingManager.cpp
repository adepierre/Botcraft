#include "botcraft/Renderer/RenderingManager.hpp"
#include "botcraft/Renderer/CubeWorldRenderer.hpp"

#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/AssetsManager.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        RenderingManager::RenderingManager(std::shared_ptr<World> world_)
        {
            world = world_;
            renderer = std::shared_ptr<Renderer::CubeWorldRenderer>(new Renderer::CubeWorldRenderer(800, 600, AssetsManager::getInstance().GetTexturesPathsNames(), CHUNK_WIDTH, false));

            running = true;
            // Launche the updating rendering thread
            m_thread_update_renderer = std::thread(&RenderingManager::WaitForRenderingUpdate, this);
        }

        RenderingManager::~RenderingManager()
        {
            running = false;

            condition_rendering.notify_all();
            if (m_thread_update_renderer.joinable())
            {
                m_thread_update_renderer.join();
            }

            renderer->Close();
        }

        std::shared_ptr<CubeWorldRenderer> RenderingManager::GetRenderer()
        {
            return renderer;
        }

        void RenderingManager::AddChunkToUpdate(const int x, const int z)
        {
            const std::vector<Position> chunk_pos = { {Position(x, 0, z), Position(x - 1, 0, z),
                            Position(x + 1, 0 , z), Position(x, 0, z - 1), Position(x, 0, z + 1)} };

            std::lock_guard<std::mutex> guard_rendering(mutex_rendering);
            for (int i = 0; i < chunk_pos.size(); ++i)
            {
                chunks_to_render.insert(chunk_pos[i]);
            }
            condition_rendering.notify_all();
        }

        void RenderingManager::WaitForRenderingUpdate()
        {
            while (running)
            {
                {
                    std::unique_lock<std::mutex> lck(mutex_rendering);
                    condition_rendering.wait(lck);
                }

                while (!chunks_to_render.empty())
                {
                    Position pos;
                    mutex_rendering.lock();
                    if (!chunks_to_render.empty())
                    {
                        auto posIterator = chunks_to_render.begin();
                        pos = *posIterator;
                        chunks_to_render.erase(posIterator);
                    }
                    mutex_rendering.unlock();

                    std::shared_ptr<const Botcraft::Chunk> chunk;
                    // Get the new values in the world
                    world->GetMutex().lock();
                    bool has_chunk_been_modified = world->HasChunkBeenModified(pos.x, pos.z);
                    if (has_chunk_been_modified)
                    {
                        chunk = world->GetChunkCopy(pos.x, pos.z);
                        world->ResetChunkModificationState(pos.x, pos.z);
                    }
                    world->GetMutex().unlock();

                    if (has_chunk_been_modified)
                    {
                        renderer->UpdateChunk(pos.x, pos.z, chunk);
                        renderer->UpdateBuffer();
                    }

                    // If we left the game, we don't need to process 
                    // the rest of the data, just discard them
                    if (!running)
                    {
                        mutex_rendering.lock();
                        chunks_to_render.clear();
                        mutex_rendering.unlock();
                        break;
                    }
                }
            }
        }

        void RenderingManager::Handle(ProtocolCraft::Message& msg)
        {

        }

        void RenderingManager::Handle(ProtocolCraft::BlockChange& msg)
        {
            Position chunk_coords = Botcraft::Chunk::BlockCoordsToChunkCoords(msg.GetLocation());
            AddChunkToUpdate(chunk_coords.x, chunk_coords.z);
        }

        void RenderingManager::Handle(ProtocolCraft::MultiBlockChange& msg)
        {
#if PROTOCOL_VERSION < 737
            AddChunkToUpdate(msg.GetChunkX(), msg.GetChunkZ());
#else
            AddChunkToUpdate((msg.GetChunkSectionCoordinate() >> 42) & 0x3FFFFF, (msg.GetChunkSectionCoordinate() >> 0) & 0x3FFFFF);
#endif
        }

        void RenderingManager::Handle(ProtocolCraft::UnloadChunk& msg)
        {
            AddChunkToUpdate(msg.GetChunkX(), msg.GetChunkZ());
        }

        void RenderingManager::Handle(ProtocolCraft::ChunkData& msg)
        {
            AddChunkToUpdate(msg.GetChunkX(), msg.GetChunkZ());
        }

        void RenderingManager::Handle(ProtocolCraft::TimeUpdate& msg)
        {
            renderer->SetDayTime(((msg.GetTimeOfDay() + 6000) % 24000) / 24000.0f);
        }

        void RenderingManager::Handle(ProtocolCraft::Respawn& msg)
        {
            renderer->RemoveAllChunks();
        }
    }
}
