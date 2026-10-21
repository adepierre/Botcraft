#pragma once

#include <atomic>
#include <vector>

#include <glm/vec3.hpp>

#include "botcraft/Renderer/BlockRenderable.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        class TransparentChunk : public BlockRenderable
        {
        public:
            TransparentChunk();
            ~TransparentChunk();

            void MarkForSort();
            void Sort(const glm::vec3& cam_pos);

        protected:
            void OnUploadedLocked() override;

        protected:
            std::vector<Face> display_faces_positions;
            std::atomic<bool> needs_sort;
        };
    } // Renderer
} // Botcraft
