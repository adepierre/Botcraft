#include "botcraft/Renderer/Face.hpp"

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
            IMatrix(const glm::mat4 &m_ = glm::mat4(1.0f))
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

        Face::Face(const FaceTransformation& transformations, const Orientation or )
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
            switch (or )
            {
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

            texture_coords = { (float)transformations.offset_x1 , (float)transformations.offset_y2, (float)transformations.offset_x2, (float)transformations.offset_y1 };
            texture_coords_overlay = texture_coords;

            texture_data = 0;
            texture_data = (texture_rotation << 1) | (display_back_face);
        }

        void Face::SetDisplayBackface(const bool display_back_face)
        {
            if (display_back_face)
            {
                texture_data |= 1UL;
            }
            else
            {
                texture_data &= ~1UL;
            }
        }

        const std::array<float, 16> &Face::GetMatrix() const
        {
            return model_matrix;
        }

        std::array<float, 16> &Face::GetMatrix()
        {
            return model_matrix;
        }

        void Face::SetTextureMultipliers(const std::array<unsigned int, 2> &mult)
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

                texture_data |= 1Ul << 3;
            }
            else
            {
                texture_coords = coords;
            }
        }
    } // Renderer
} // Botcraft