#pragma once

#include "botcraft/Renderer/BlockRenderable.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        class Chunk : public BlockRenderable
        {
        public:
            Chunk();
            ~Chunk();

            void Update();
            void AddFace(const Face &f, const std::array<unsigned int, 2>& texture_multipliers,
                const float offset_x, const float offset_y, const float offset_z);
        };
    } // Renderer
} // Botcraft