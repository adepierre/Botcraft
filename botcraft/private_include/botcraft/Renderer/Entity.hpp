#pragma once

#include "botcraft/Renderer/BlockRenderable.hpp"

#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        class Entity : public BlockRenderable
        {
        public:
            Entity(const std::vector<Face>& faces_);
            ~Entity();

            void Update();
            void UpdateFaces(const std::vector<Face>& faces_);
        };
    } // Renderer
} // Botcraft