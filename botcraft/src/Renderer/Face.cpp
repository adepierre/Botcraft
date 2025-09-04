#include "botcraft/Renderer/Face.hpp"
#include "botcraft/Renderer/Transformation.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Botcraft
{
    namespace Renderer
    {
        //To avoid including glm in public header
        struct IMatrix
        {
            IMatrix(const glm::mat4& m_ = glm::mat4(1.0f))
            {
                m = m_;
            }

            glm::mat4 m;
        };

        const std::vector<float> Face::base_face = {
            //   x         y         z
            -0.9999f, -0.9999f, -0.9999f,
            0.9999f, -0.9999f, -0.9999f,
            -0.9999f, -0.9999f, 0.9999f,
            0.9999f, -0.9999f, 0.9999f
        };

        Face::Face()
        {

        }

        Face::Face(const FaceTransformation& transformations, const Orientation orientation)
        {
            IMatrix model;

            //Apply the translations of the model
            for (int i = 0; i < transformations.translations.size(); ++i)
            {
                transformations.translations[i]->ApplyTransformation(model);
            }

            //Apply the rotations
            for (int i = 0; i < transformations.rotations.size(); ++i)
            {
                transformations.rotations[i]->ApplyTransformation(model);
            }

            //Apply the scales
            unsigned int display_back_face = 1;
            for (int i = 0; i < transformations.scales.size(); ++i)
            {
                transformations.scales[i]->ApplyTransformation(model);
                if (abs(transformations.scales[i]->axis_x) < 0.001f ||
                    abs(transformations.scales[i]->axis_y) < 0.001f ||
                    abs(transformations.scales[i]->axis_z) < 0.001f)
                {
                    display_back_face = 0;
                }
            }

            //Apply the transformations to get the good face from the base one
            switch (orientation)
            {
            case Orientation::None:
            case Orientation::Bottom:
                // No rotation needed
                break;
            case Orientation::Top:
                model.m = glm::rotate(model.m, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model.m = glm::rotate(model.m, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case Orientation::East:
                model.m = glm::rotate(model.m, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model.m = glm::rotate(model.m, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case Orientation::West:
                model.m = glm::rotate(model.m, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model.m = glm::rotate(model.m, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case Orientation::North:
                model.m = glm::rotate(model.m, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model.m = glm::rotate(model.m, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case Orientation::South:
                model.m = glm::rotate(model.m, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                break;
            }

            unsigned char texture_rotation = transformations.rotation;
            while (texture_rotation < 0)
            {
                texture_rotation += 4;
            }
            while (texture_rotation > 3)
            {
                texture_rotation -= 4;
            }

            const float* model_ptr = glm::value_ptr(model.m);

            for (int i = 0; i < 16; ++i)
            {
                model_matrix[i] = model_ptr[i];
            }

            texture_coords = {
                static_cast<float>(transformations.offset_x1),
                static_cast<float>(transformations.offset_y2),
                static_cast<float>(transformations.offset_x2),
                static_cast<float>(transformations.offset_y1)
            };
            texture_coords_overlay = texture_coords;

            texture_data = 0;
            texture_data = (texture_rotation << 3) | (display_back_face << 2);
        }

        void Face::SetTransparencyData(const Transparency transparency)
        {
            // 0 0 means opaque
            // 0 1 means fully transparent
            // 1 1 means partially transparent
            switch (transparency)
            {
            case Transparency::Opaque:
                texture_data &= ~3UL;
                break;
            case Transparency::Total:
                texture_data |= 1UL;
                texture_data &= ~2UL;
                break;
            case Transparency::Partial:
                texture_data |= 3UL;
                break;
            }
        }

        Transparency Face::GetTransparencyData() const
        {
            switch (texture_data & 3UL)
            {
            case 0:
                return Transparency::Opaque;
            case 1:
                return Transparency::Total;
            case 3:
                return Transparency::Partial;
            default:
                return Transparency::Opaque;
            }
        }

        void Face::SetDisplayBackface(const bool display_backface)
        {
            if (display_backface)
            {
                texture_data |= 1Ul << 2;
            }
            else
            {
                texture_data &= (~1Ul) << 2;
            }
        }

        const std::array<float, 16>& Face::GetMatrix() const
        {
            return model_matrix;
        }

        std::array<float, 16>& Face::GetMatrix()
        {
            return model_matrix;
        }

        void Face::SetTextureMultipliers(const std::array<unsigned int, 2>& mult)
        {
            texture_multipliers = mult;
        }

        const std::array<float, 4>& Face::GetTextureCoords(const bool overlay) const
        {
            if (overlay)
            {
                return texture_coords_overlay;
            }
            return texture_coords;
        }

        void Face::SetTextureCoords(const std::array<float, 4>& coords, const bool overlay)
        {
            if (overlay)
            {
                texture_coords_overlay = coords;

                texture_data |= 1Ul << 5;
            }
            else
            {
                texture_coords = coords;
            }
        }

        void Face::UpdateMatrix(const FaceTransformation& transformations, const Orientation orientation)
        {
            IMatrix model;

            //Apply the translations of the model
            for (int i = 0; i < transformations.translations.size(); ++i)
            {
                transformations.translations[i]->ApplyTransformation(model);
            }

            //Apply the rotations
            for (int i = 0; i < transformations.rotations.size(); ++i)
            {
                transformations.rotations[i]->ApplyTransformation(model);
            }

            //Apply the scales
            for (int i = 0; i < transformations.scales.size(); ++i)
            {
                transformations.scales[i]->ApplyTransformation(model);
            }

            //Apply the transformations to get the good face from the base one
            switch (orientation)
            {
            case Orientation::None:
            case Orientation::Bottom:
                // No rotation needed
            case Orientation::Top:
                model.m = glm::rotate(model.m, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model.m = glm::rotate(model.m, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case Orientation::East:
                model.m = glm::rotate(model.m, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model.m = glm::rotate(model.m, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case Orientation::West:
                model.m = glm::rotate(model.m, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model.m = glm::rotate(model.m, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case Orientation::North:
                model.m = glm::rotate(model.m, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model.m = glm::rotate(model.m, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case Orientation::South:
                model.m = glm::rotate(model.m, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                break;
            }

            const float* model_ptr = glm::value_ptr(model.m);

            for (int i = 0; i < 16; ++i)
            {
                model_matrix[i] = model_ptr[i];
            }
        }
    } // Renderer
} // Botcraft
