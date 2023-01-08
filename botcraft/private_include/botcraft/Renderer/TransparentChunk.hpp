#pragma once

#include <vector>

#include <glm/vec3.hpp>

#include "botcraft/Renderer/Chunk.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        class TransparentChunk : public Chunk
        {
        public:
            TransparentChunk();
            ~TransparentChunk();

            void SetDisplayStatus(const BufferStatus s);
            void Sort(const glm::vec3 &cam_pos);
            void Update();

        protected:
            std::vector<Face> display_faces_positions;
            BufferStatus display_buffer_status;
        };
    } // Renderer
} // Botcraft