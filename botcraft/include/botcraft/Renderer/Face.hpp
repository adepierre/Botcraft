#pragma once

#include <map>
#include <array>
#include <vector>
#include <memory>
#include <deque>

#include "botcraft/Game/Enums.hpp"

#include "botcraft/Renderer/Transformation.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        struct IMatrix;

        class Face
        {
        public:
            Face();
            Face(const FaceTransformation &transformations, const Orientation or);

            bool operator ==(const Face &other) const
            {
                //Texture doesn't matter
                for (int i = 0; i < 16; ++i)
                {
                    if (model_matrix[i] != other.model_matrix[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            void SetDisplayBackface(const bool display_back_face);

            const std::array<float, 16> &GetMatrix() const;
            std::array<float, 16> &GetMatrix();
            void SetTextureMultipliers(const std::array<unsigned int, 2> &mult);
            const std::array<float, 4>& GetTextureCoords(const bool overlay) const;
            void SetTextureCoords(const std::array<float, 4>& coords, const bool overlay);

            static const std::vector<float> base_face;

        private:
            // Model matrix, 16 floats
            std::array<float, 16> model_matrix;

            // Texture coordinates for both base texture and optional overlay
            // (u1, v1, u2, v2)
            std::array<float, 4> texture_coords;
            std::array<float, 4> texture_coords_overlay;

            //One int with all textures data packed inside
            //(unused : 28 bits, use_overlay : 1 bit, rotation : 2 bits, display_backface : 1 bit)
            unsigned int texture_data;

            //One int with texture multiplier packed inside (rgba) x2 for one optional overlay
            std::array<unsigned int, 2> texture_multipliers;
        };
    } // Renderer
} // Botcraft

namespace std
{
    template<>
    struct hash<Botcraft::Renderer::Face>
    {
        inline size_t operator()(const Botcraft::Renderer::Face &f) const
        {
            const std::array<float, 16> &matrix = f.GetMatrix();
            std::hash<float> hasher;
            size_t value = hasher(matrix[0]);

            for (int i = 1; i < 16; ++i)
            {
                value ^= hasher(matrix[i]) + 0x9e3779b9 + (value << 6) + (value >> 2);
            }
            return value;
        }
    };
}