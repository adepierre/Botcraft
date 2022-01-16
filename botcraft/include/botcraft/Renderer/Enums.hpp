#pragma once

namespace Botcraft
{
    namespace Renderer
    {
        /// @brief Transparency values for textures
        enum class Transparency
        {
            Opaque, // Alpha = 255
            Total,  // Alpha == 0
            Partial // 0 < Alpha < 255
        };

        /// @brief Animation status of a texture
        enum class Animation
        {
            Static,
            Animated
        };
    } // Renderer
} // Botcraft
