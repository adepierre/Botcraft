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

        Face::Face(const FaceTransformation &transformations, const Orientation or)
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
            switch (or)
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

            const float *model_ptr = glm::value_ptr(model.m);

            for (int i = 0; i < 16; ++i)
            {
                model_matrix[i] = model_ptr[i];
            }

            unsigned char offset_x1 = std::max((unsigned char)0, transformations.offset_x1);
            unsigned char offset_y1 = std::max((unsigned char)0, transformations.offset_y1);
            unsigned char offset_x2 = std::min((unsigned char)16, transformations.offset_x2);
            unsigned char offset_y2 = std::min((unsigned char)16, transformations.offset_y2);

            texture_data = (texture_rotation << 21) | (display_back_face << 20) | (offset_x2 << 15) | (offset_x1 << 10) | ((16 - offset_y1) << 5) | (16 - offset_y2);
        }

        void Face::SetDisplayBackface(const bool display_back_face)
        {
            if (display_back_face)
            {
                texture_data |= 1UL << 20;
            }
            else
            {
                texture_data &= ~(1UL << 20);
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

        void Face::SetAtlasCoords(const std::array<unsigned short, 4> &coords)
        {
            atlas_coords = coords;

            // Set use_overlay bit
            if (atlas_coords[2] != 0 || atlas_coords[3] != 0)
            {
                texture_data |= 1UL << 23;
            }
            else
            {
                texture_data &= ~(1UL << 23);
            }
        }

        void Face::SetTextureMultipliers(const std::array<unsigned int, 2> &mult)
        {
            texture_multipliers = mult;
        }
    } // Renderer
} // Botcraft