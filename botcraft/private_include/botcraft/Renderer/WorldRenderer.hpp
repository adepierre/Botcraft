#pragma once

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Renderer/Face.hpp"

#include <glm/glm.hpp>

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
        class Chunk;
        class Entity;
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

        class WorldRenderer
        {
        public:
            // Constructor
            WorldRenderer(const unsigned int section_height_);
            ~WorldRenderer();

            std::shared_ptr<Camera> GetCamera();

            void InitGL();
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
            // Add a face to the rendering data
            // It will not be rendered until the next frame with
            // blocks_faces_should_be_updated set to true
            void AddFace(const Position& block_pos, const Vector3<double>& offset, const Face& face_,
                const std::vector<std::string>& texture_identifiers_,
                const std::vector<unsigned int>& texture_multipliers_);

            // Returns the color modifier (for redstone/leaves/water etc...)
            const std::vector<unsigned int> GetColorModifier(const int y, const Biome* biome, const Blockstate* blockstate, const std::vector<bool>& use_tintindex) const;

            // Returns the distance from the center of the chunk to the camera
            const float DistanceToCamera(const Position& chunk) const;


        private:
            unsigned int view_uniform_buffer;

            // Each chunk faces are stored in rendering sections,
            // They don't need to be the same size as real
            // sections
            unsigned int section_height;

            std::unordered_map<Position, std::shared_ptr<Chunk> > chunks;
            std::mutex chunks_mutex;
            std::unordered_map<Position, std::shared_ptr<TransparentChunk> > transparent_chunks;
            std::mutex transparent_chunks_mutex;
            bool blocks_faces_should_be_updated;

            std::unordered_map<int, std::shared_ptr<Entity> > entities;
            std::mutex entities_mutex;
            bool entities_faces_should_be_updated;

            std::shared_ptr<Camera> camera;
            std::mutex m_mutex_camera;

            unsigned int atlas_texture;
        };
    } // Renderer
} // Botcraft