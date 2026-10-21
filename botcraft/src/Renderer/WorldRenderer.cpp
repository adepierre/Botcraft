#include "botcraft/Renderer/Atlas.hpp"
#include "botcraft/Renderer/Camera.hpp"
#include "botcraft/Renderer/Entity.hpp"
#include "botcraft/Renderer/TransparentChunk.hpp"
#include "botcraft/Renderer/WorldRenderer.hpp"

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/World/Biome.hpp"
#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Game/World/Chunk.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <iterator>
#include <unordered_set>

namespace Botcraft
{
    namespace Renderer
    {
        namespace
        {
            std::array<unsigned int, 2> ToMultipliers(const std::vector<unsigned int>& v);

            Position SectionOf(const Position& block_pos);

            template<class ChunkPtr>
            void ReplaceColumn(
                std::unordered_map<Position, std::shared_ptr<ChunkPtr>>& renderables,
                std::mutex& mutex,
                std::atomic<bool>& dirty,
                const int x, const int z,
                std::unordered_map<Position, std::vector<Face>>&& new_faces
            );
        }

        WorldRenderer::WorldRenderer()
        {
            view_uniform_buffer = 0;
            atlas_texture = 0;

            chunks = std::unordered_map<Position, std::shared_ptr<Chunk> >();
            transparent_chunks = std::unordered_map<Position, std::shared_ptr<TransparentChunk> >();

            chunks_dirty = true;
            transparent_chunks_dirty = true;

            entities = std::unordered_map<int, std::shared_ptr<Entity> >();
            entities_faces_should_be_updated = true;

            camera = std::make_shared<Camera>();
        }

        WorldRenderer::~WorldRenderer()
        {
            camera.reset();
        }

        std::shared_ptr<Camera> WorldRenderer::GetCamera()
        {
            return camera;
        }

        void WorldRenderer::InitGL()
        {
            glGenBuffers(1, &view_uniform_buffer);
            glBindBuffer(GL_UNIFORM_BUFFER, view_uniform_buffer);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            glBindBufferRange(GL_UNIFORM_BUFFER, 0, view_uniform_buffer, 0, sizeof(glm::mat4));

            //Create a texture
            glGenTextures(1, &atlas_texture);
            glBindTexture(GL_TEXTURE_2D, atlas_texture);

            //Options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            const Atlas* atlas = AssetsManager::getInstance().GetAtlas();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas->GetWidth(), atlas->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, atlas->Get());
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void WorldRenderer::ReleaseGL()
        {
            {
                std::lock_guard<std::mutex> lock(chunks_mutex);
                chunks.clear();
            }
            {
                std::lock_guard<std::mutex> lock(transparent_chunks_mutex);
                transparent_chunks.clear();
            }
            {
                std::lock_guard<std::mutex> lock(entities_mutex);
                entities.clear();
            }

            if (view_uniform_buffer != 0)
            {
                glDeleteBuffers(1, &view_uniform_buffer);
                view_uniform_buffer = 0;
            }
            if (atlas_texture != 0)
            {
                glDeleteTextures(1, &atlas_texture);
                atlas_texture = 0;
            }
        }

        void WorldRenderer::UpdateViewMatrix()
        {
            if (camera->GetHasChangedOrientation() || camera->GetHasChangedPosition())
            {
                glm::mat4 view_matrix = camera->GetViewMatrix();
                if (camera->GetHasChangedPosition())
                {
                    transparent_chunks_mutex.lock();
                    for (auto it = transparent_chunks.begin(); it != transparent_chunks.end(); ++it)
                    {
                        it->second->MarkForSort();
                    }
                    transparent_chunks_mutex.unlock();
                }
                camera->ResetHasChangedPosition();
                camera->ResetHasChangedOrientation();
                glBindBuffer(GL_UNIFORM_BUFFER, view_uniform_buffer);
                glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view_matrix));
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
            }
        }

        void WorldRenderer::SetCameraProjection(const glm::mat4& proj)
        {
            camera->SetProjection(proj);
        }

        void WorldRenderer::UpdateFaces()
        {
            if (chunks_dirty.load(std::memory_order_relaxed))
            {
                std::lock_guard<std::mutex> lock(chunks_mutex);
                if (chunks_dirty.exchange(false))
                {
                    for (auto it = chunks.begin(); it != chunks.end();)
                    {
                        it->second->Update();
                        it = it->second->GetNumFace() == 0 ? chunks.erase(it) : std::next(it);
                    }
                }
            }

            if (transparent_chunks_dirty.load(std::memory_order_relaxed))
            {
                std::lock_guard<std::mutex> lock(transparent_chunks_mutex);
                if (transparent_chunks_dirty.exchange(false))
                {
                    for (auto it = transparent_chunks.begin(); it != transparent_chunks.end();)
                    {
                        it->second->Update();
                        it = it->second->GetNumFace() == 0 ? transparent_chunks.erase(it) : std::next(it);
                    }
                }
            }

            if (entities_faces_should_be_updated.load(std::memory_order_relaxed))
            {
                std::lock_guard<std::mutex> lock(entities_mutex);
                if (entities_faces_should_be_updated.exchange(false))
                {
                    for (auto it = entities.begin(); it != entities.end();)
                    {
                        it->second->Update();
                        it = it->second->GetNumFace() == 0 ? entities.erase(it) : std::next(it);
                    }
                }
            }
        }

        void WorldRenderer::UpdateChunk(const int x_, const int z_, const std::optional<Botcraft::Chunk>& chunk)
        {
            if (!chunk.has_value())
            {
                ReplaceColumn(chunks, chunks_mutex, chunks_dirty, x_, z_, {});
                ReplaceColumn(transparent_chunks, transparent_chunks_mutex, transparent_chunks_dirty, x_, z_, {});
                return;
            }

            std::unordered_map<Position, std::vector<Face>> opaque_faces;
            std::unordered_map<Position, std::vector<Face>> transparent_faces;
            // For each block in the chunk, check its neighbours
            // to see which face to draw
            const std::vector<Position> neighbour_positions({ Position(0, -1, 0), Position(0, 0, -1),
                            Position(-1, 0, 0), Position(1, 0, 0), Position(0, 0, 1), Position(0, 1, 0) });

            std::vector<const Blockstate*> neighbour_blockstates(6);

            Position pos;
            for (int y = chunk->GetMinY(); y < chunk->GetHeight() + chunk->GetMinY(); ++y)
            {
                pos.y = y;
                for (int z = 0; z < CHUNK_WIDTH; ++z)
                {
                    pos.z = z;
                    for (int x = 0; x < CHUNK_WIDTH; ++x)
                    {
                        pos.x = x;

                        // If this block is air, just skip it
                        const Blockstate* this_block = chunk->GetBlock(pos);
                        if (this_block == nullptr || this_block->IsAir())
                        {
                            continue;
                        }

                        // Else check its neighbours to find which face to draw
                        for (int i = 0; i < 6; ++i)
                        {
                            neighbour_blockstates[i] = chunk->GetBlock(pos + neighbour_positions[i]);
                        }

                        bool is_surrounded_by_opaque = false;
                        //Check if this block is sourrounded by non transparent blocks
                        for (int i = 0; i < neighbour_positions.size(); ++i)
                        {
                            if (neighbour_blockstates[i] == nullptr ||
                                neighbour_blockstates[i]->IsTransparent())
                            {
                                break;
                            }

                            //If we are here, all the neigbhours are non transparent blocks, so
                            //there is no face to add to the renderer
                            if (i == neighbour_positions.size() - 1)
                            {
                                is_surrounded_by_opaque = true;
                            }
                        }

                        if (is_surrounded_by_opaque)
                        {
                            continue;
                        }

                        //Add all faces of the current state
                        const Position block_pos(
                            pos.x + CHUNK_WIDTH * x_,
                            pos.y,
                            pos.z + CHUNK_WIDTH * z_
                        );
                        const std::vector<FaceDescriptor>& current_faces = this_block->GetModel(this_block->GetModelId(block_pos)).GetFaces();
                        const Vector3<double> offset = this_block->GetHorizontalOffsetAtPos(block_pos);
#if PROTOCOL_VERSION < 552 /* < 1.15 */
                        const Biome* current_biome = chunk->GetBiome(x, z);
#else
                        const Biome* current_biome = chunk->GetBiome(x, y, z);
#endif

                        for (int i = 0; i < current_faces.size(); ++i)
                        {
                            //Check if the neighbour in this direction is hidding this face
                            // We also remove the faces between two transparent blocks with the same names
                            // (example: faces between two water blocks)
                            if (current_faces[i].cullface_direction == Orientation::None ||
                                !neighbour_blockstates[static_cast<int>(current_faces[i].cullface_direction)] ||
                                (neighbour_blockstates[static_cast<int>(current_faces[i].cullface_direction)]->IsTransparent() &&
                                    neighbour_blockstates[static_cast<int>(current_faces[i].cullface_direction)]->GetName() != this_block->GetName())
                                )
                            {
                                Face f = current_faces[i].face;
                                // Add 0.5 because the origin of the block is at the center
                                // but the coordinates start from the block corner
                                f.GetMatrix()[12] += static_cast<float>(offset.x) + 0.5f;
                                f.GetMatrix()[13] += static_cast<float>(offset.y) + 0.5f;
                                f.GetMatrix()[14] += static_cast<float>(offset.z) + 0.5f;
                                f.SetTextureMultipliers(ToMultipliers(GetColorModifier(pos.y, current_biome, this_block, current_faces[i].use_tintindexes)));

                                std::unordered_map<Position, std::vector<Face>>& target = f.GetTransparencyData() == Transparency::Partial ? transparent_faces : opaque_faces;
                                target[SectionOf(block_pos)].push_back(std::move(f));
                            }
                        }
                    }
                }
            }
            ReplaceColumn(chunks, chunks_mutex, chunks_dirty, x_, z_, std::move(opaque_faces));
            ReplaceColumn(transparent_chunks, transparent_chunks_mutex, transparent_chunks_dirty, x_, z_, std::move(transparent_faces));
        }

        void WorldRenderer::UpdateEntity(const int id, const std::vector<Face>& faces)
        {
            std::lock_guard<std::mutex> lock(entities_mutex);

            auto it = entities.find(id);

            if (it == entities.end() && faces.size() != 0)
            {
                entities[id] = std::make_shared<Entity>(faces);
                entities_faces_should_be_updated = true;
            }
            else if (it != entities.end() && faces.size() == 0)
            {
                it->second->ClearFaces();
                entities_faces_should_be_updated = true;
            }
            else if (it != entities.end())
            {
                it->second->SetFaces(std::vector<Face>(faces.begin(), faces.end()));
                entities_faces_should_be_updated = true;
            }
        }

        void WorldRenderer::UseAtlasTextureGL()
        {
            glBindTexture(GL_TEXTURE_2D, atlas_texture);
        }

        void WorldRenderer::ClearFaces()
        {
            // We simply remove all the faces from all the chunks
            // The chunks will be deleted on the next frame
            {
                std::lock_guard<std::mutex> lock(chunks_mutex);
                for (auto it = chunks.begin(); it != chunks.end(); it++)
                {
                    it->second->ClearFaces();
                }
            }
            {
                std::lock_guard<std::mutex> lock(transparent_chunks_mutex);
                for (auto it = transparent_chunks.begin(); it != transparent_chunks.end(); it++)
                {
                    it->second->ClearFaces();
                }
            }
            {
                std::lock_guard<std::mutex> lock(entities_mutex);
                for (auto it = entities.begin(); it != entities.end(); it++)
                {
                    it->second->ClearFaces();
                }
            }
            chunks_dirty = true;
            transparent_chunks_dirty = true;
            entities_faces_should_be_updated = true;
        }

        void WorldRenderer::SetPosOrientation(const double x_, const double y_, const double z_, const float yaw_, const float pitch_)
        {
            if (camera)
            {
                camera->SetPosition(
                    static_cast<float>(x_),
                    static_cast<float>(y_),
                    static_cast<float>(z_)
                );
                camera->SetRotation(pitch_, yaw_);
            }
        }

        void WorldRenderer::RenderFaces(int* num_chunks_, int* num_rendered_chunks_,
            int* num_entities_, int* num_rendered_entities_,
            int* num_faces_, int* num_rendered_faces_)
        {
            const std::array<glm::vec4, 6>& frustum_planes = camera->GetFrustumPlanes();

            // Get a list of all loaded chunks
            std::unordered_set<Position> all_loaded_chunks;
            all_loaded_chunks.reserve(chunks.size() + transparent_chunks.size());
            int num_faces = 0;

            chunks_mutex.lock();
            for (auto it = chunks.begin(); it != chunks.end(); ++it)
            {
                all_loaded_chunks.insert(it->first);
                num_faces += it->second->GetNumFace();
            }
            chunks_mutex.unlock();
            transparent_chunks_mutex.lock();
            for (auto it = transparent_chunks.begin(); it != transparent_chunks.end(); ++it)
            {
                all_loaded_chunks.insert(it->first);
                num_faces += it->second->GetNumFace();
            }
            transparent_chunks_mutex.unlock();
            const int num_chunks = static_cast<int>(all_loaded_chunks.size());

            // Apply frustum culling to render only the visible ones
            std::vector<Position> chunks_to_render;
            chunks_to_render.reserve(all_loaded_chunks.size());
            std::unordered_map<Position, bool> inside_frustum;
            // Frustum culling algorithm from http://old.cescg.org/CESCG-2002/DSykoraJJelinek/
            for (auto it = all_loaded_chunks.begin(); it != all_loaded_chunks.end(); ++it)
            {
                FrustumResult result = FrustumResult::Inside;

                const float min_x = static_cast<float>(CHUNK_WIDTH * (*it).x);
                const float max_x = static_cast<float>(CHUNK_WIDTH * ((*it).x + 1));
                const float min_y = static_cast<float>(static_cast<int>(RENDERING_SECTION_HEIGHT) * (*it).y);
                const float max_y = static_cast<float>(static_cast<int>(RENDERING_SECTION_HEIGHT) * ((*it).y + 1));
                const float min_z = static_cast<float>(CHUNK_WIDTH * (*it).z);
                const float max_z = static_cast<float>(CHUNK_WIDTH * ((*it).z + 1));

                for (int i = 0; i < 6; ++i)
                {
                    const bool sign_x = frustum_planes[i].x > 0.0f;
                    const bool sign_y = frustum_planes[i].y > 0.0f;
                    const bool sign_z = frustum_planes[i].z > 0.0f;

                    const glm::vec4 p_vertex = glm::vec4(sign_x ? max_x : min_x, sign_y ? max_y : min_y, sign_z ? max_z : min_z, 1.0f);

                    if (glm::dot(frustum_planes[i], p_vertex) < 0.0f)
                    {
                        result = FrustumResult::Outside;
                        break;
                    }

                    const glm::vec4 n_vertex = glm::vec4(sign_x ? min_x : max_x, sign_y ? min_y : max_y, sign_z ? min_z : max_z, 1.0f);

                    if (glm::dot(frustum_planes[i], n_vertex) < 0.0f)
                    {
                        result = FrustumResult::Intersect;
                    }
                }

                inside_frustum[*it] = result != FrustumResult::Outside;
                if (result != FrustumResult::Outside)
                {
                    chunks_to_render.push_back(*it);
                }
            }

            // Sort the chunks from far to near the camera (necessary for transparent chunks to render in the right order)
            std::sort(chunks_to_render.begin(), chunks_to_render.end(), [this](const Position& p1, const Position& p2) {return this->DistanceToCamera(p1) > this->DistanceToCamera(p2); });

            // Render all non partially transparent faces
            const int num_rendered_chunks = static_cast<int>(chunks_to_render.size());
            int num_rendered_faces = 0;
            chunks_mutex.lock();
            for (int i = 0; i < num_rendered_chunks; ++i)
            {
                auto found_it = chunks.find(chunks_to_render[i]);
                if (found_it != chunks.end())
                {
                    found_it->second->Render();
                    num_rendered_faces += found_it->second->GetNumFace();
                }
            }
            chunks_mutex.unlock();

            // Render entities, with approximate frustum culling
            const std::vector<Position> neighbouring_positions({ Position(0, 0, 0), Position(0, -1, 0), Position(0, 0, -1),
                            Position(-1, 0, 0), Position(1, 0, 0), Position(0, 0, 1), Position(0, 1, 0) });
            entities_mutex.lock();
            const int num_entities = static_cast<int>(entities.size());
            int num_rendered_entities = 0;
            for (auto& e : entities)
            {
                num_faces += e.second->GetNumFace();

                const Vector3<float> approx_pos = e.second->GetApproxPos();
                const Position chunk_position(
                    static_cast<int>(floor(approx_pos.x / static_cast<double>(CHUNK_WIDTH))),
                    static_cast<int>(floor(approx_pos.y / static_cast<double>(RENDERING_SECTION_HEIGHT))),
                    static_cast<int>(floor(approx_pos.z / static_cast<double>(CHUNK_WIDTH)))
                );

                for (int i = 0; i < neighbouring_positions.size(); ++i)
                {
                    if (inside_frustum[chunk_position + neighbouring_positions[i]])
                    {
                        e.second->Render();
                        num_rendered_entities += 1;
                        num_rendered_faces += e.second->GetNumFace();
                        break;
                    }
                }
            }
            entities_mutex.unlock();

            const glm::vec3 cam_pos = camera->GetPosition();

            // Render all partially transparent faces
            transparent_chunks_mutex.lock();
            for (int i = 0; i < num_rendered_chunks; ++i)
            {
                auto found_it = transparent_chunks.find(chunks_to_render[i]);
                if (found_it != transparent_chunks.end())
                {
                    found_it->second->Sort(cam_pos);
                    found_it->second->Render();
                    num_rendered_faces += found_it->second->GetNumFace();
                }
            }
            transparent_chunks_mutex.unlock();

            if (num_chunks_)
            {
                *num_chunks_ = num_chunks;
            }
            if (num_rendered_chunks_)
            {
                *num_rendered_chunks_ = num_rendered_chunks;
            }
            if (num_faces_)
            {
                *num_faces_ = num_faces;
            }
            if (num_rendered_faces_)
            {
                *num_rendered_faces_ = num_rendered_faces;
            }
            if (num_entities_)
            {
                *num_entities_ = num_entities;
            }
            if (num_rendered_entities_)
            {
                *num_rendered_entities_ = num_rendered_entities;
            }
        }

        const std::vector<unsigned int> WorldRenderer::GetColorModifier(const int y, const Biome* biome, const Blockstate* blockstate, const std::vector<bool>& use_tintindex) const
        {
            std::vector<unsigned int> texture_modifier(use_tintindex.size(), 0xFFFFFFFF);
            for (int i = 0; i < use_tintindex.size(); ++i)
            {
                switch (blockstate->GetTintType())
                {
                case TintType::None:
                    break;
                case TintType::Grass:
                    if (use_tintindex[i])
                    {
                        if (biome)
                        {
                            texture_modifier[i] = biome->GetColorMultiplier(y, true);
                        }
                    }
                    break;
                case TintType::Leaves:
                    if (use_tintindex[i])
                    {
                        if (biome)
                        {
                            texture_modifier[i] = biome->GetColorMultiplier(y, false);
                        }
                    }
                    break;
                    // Black when signal strength is 0 and red when it's 15
                case TintType::Redstone:
#if PROTOCOL_VERSION == 340 /* 1.12.2 */
                    texture_modifier[i] = 0xFF000000 | (25 + 15 * blockstate->GetId().second);
#else
                    texture_modifier[i] = 0xFF000000 | (25 + 15 * std::stoi(blockstate->GetVariableValue("power")));
#endif
                    break;
                case TintType::Water:
                    if (biome)
                    {
                        texture_modifier[i] = biome->GetWaterColorMultiplier();
                    }
                    break;
                default:
                    break;
                }
            }
            return texture_modifier;
        }

        const float WorldRenderer::DistanceToCamera(const Position& chunk) const
        {
            return camera->GetDistance(CHUNK_WIDTH * (chunk.x + 0.5f), RENDERING_SECTION_HEIGHT * (chunk.y + 0.5f), CHUNK_WIDTH * (chunk.z + 0.5f));
        }

        namespace
        {
            std::array<unsigned int, 2> ToMultipliers(const std::vector<unsigned int>& v)
            {
                std::array<unsigned int, 2> out = { 0xFFFFFFFF, 0xFFFFFFFF };
                for (int i = 0; i < std::min(2, static_cast<int>(v.size())); ++i)
                {
                    out[i] = v[i];
                }
                return out;
            }

            Position SectionOf(const Position& block_pos)
            {
                return Position(
                    static_cast<int>(std::floor(block_pos.x / static_cast<double>(CHUNK_WIDTH))),
                    static_cast<int>(std::floor(block_pos.y / static_cast<double>(RENDERING_SECTION_HEIGHT))),
                    static_cast<int>(std::floor(block_pos.z / static_cast<double>(CHUNK_WIDTH)))
                );
            }

            template<class ChunkPtr>
            void ReplaceColumn(
                std::unordered_map<Position, std::shared_ptr<ChunkPtr>>& renderables,
                std::mutex& mutex,
                std::atomic<bool>& dirty,
                const int x, const int z,
                std::unordered_map<Position, std::vector<Face>>&& new_faces
            )
            {
                bool changed = false;
                std::lock_guard<std::mutex> lock(mutex);

                for (auto& [pos, renderable] : renderables)
                {
                    if (pos.x == x && pos.z == z && new_faces.find(pos) == new_faces.end())
                    {
                        renderable->SetFaces({});
                        changed = true;
                    }
                }

                for (auto& [pos, faces] : new_faces)
                {
                    std::shared_ptr<ChunkPtr>& r = renderables[pos];
                    if (r == nullptr)
                    {
                        r = std::make_shared<ChunkPtr>();
                    }
                    r->SetFaces(std::move(faces));
                    changed = true;
                }

                if (changed)
                {
                    dirty = true;
                }
            }
        }
    } // Renderer
} // Botcraft
