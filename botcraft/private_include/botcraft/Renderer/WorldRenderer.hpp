#pragma once

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Renderer/Face.hpp"

#include <glm/glm.hpp>

#include <atomic>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Botcraft
{
    class Biome;
    class Blockstate;
    class Chunk;
    class Entity;

    namespace Renderer
    {
        class Entity;
        class BlockRenderable;
        using Chunk = BlockRenderable;
        class TransparentChunk;
        class Camera;
        class Atlas;

        // Intersection test for frustum culling
        enum class FrustumResult
        {
            Outside = 0, // Box is outside the frustum
            Intersect,   // Box intersects with the frustum
            Inside         // Box is inside the frustum
        };

        // Each chunk faces are stored in rendering sections,
        // They don't need to be the same size as real sections
        static constexpr unsigned int RENDERING_SECTION_HEIGHT = 16;

        class WorldRenderer
        {
        public:
            // Constructor
            WorldRenderer();
            ~WorldRenderer();

            std::shared_ptr<Camera> GetCamera();

            void InitGL();
            void ReleaseGL();
            void UpdateViewMatrix();
            void SetCameraProjection(const glm::mat4& proj);
            void UpdateFaces();
            void UpdateChunk(const int x_, const int z_, const std::optional<Botcraft::Chunk>& chunk);
            void UpdateEntity(const int id, const std::vector<Face>& faces);
            void UseAtlasTextureGL();
            void ClearFaces();

            // Set camera position and orientation
            void SetPosOrientation(const double x_, const double y_, const double z_, const float yaw_, const float pitch_);

            // Render all the faces (chunks + partially transparent chunks + entities)
            // Optional pointer can be passed to get statistics
            void RenderFaces(int* num_chunks_ = nullptr, int* num_rendered_chunks_ = nullptr,
                int* num_entities_ = nullptr, int* num_rendered_entities_ = nullptr,
                int* num_faces_ = nullptr, int* num_rendered_faces_ = nullptr);

        private:
            // Returns the color modifier (for redstone/leaves/water etc...)
            const std::vector<unsigned int> GetColorModifier(const int y, const Biome* biome, const Blockstate* blockstate, const std::vector<bool>& use_tintindex) const;

            // Returns the distance from the center of the chunk to the camera
            const float DistanceToCamera(const Position& chunk) const;


        private:
            unsigned int view_uniform_buffer;

            std::unordered_map<Position, std::shared_ptr<Chunk> > chunks;
            std::mutex chunks_mutex;
            std::unordered_map<Position, std::shared_ptr<TransparentChunk> > transparent_chunks;
            std::mutex transparent_chunks_mutex;
            std::atomic<bool> chunks_dirty;
            std::atomic<bool> transparent_chunks_dirty;

            std::unordered_map<int, std::shared_ptr<Entity> > entities;
            std::mutex entities_mutex;
            std::atomic<bool> entities_faces_should_be_updated;

            std::shared_ptr<Camera> camera;

            unsigned int atlas_texture;
        };
    } // Renderer
} // Botcraft
