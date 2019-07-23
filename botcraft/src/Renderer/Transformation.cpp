#include "botcraft/Renderer/Transformation.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Botcraft
{
    namespace Renderer
    {
        //To avoid to include glm in header
        struct IMatrix
        {
            IMatrix(const glm::mat4 &m_ = glm::mat4(0.0f))
            {
                m = m_;
            }

            glm::mat4 m;
        };

        Translation::Translation(const float x_, const float y_, const float z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }

        void Translation::ApplyTransformation(IMatrix &m) const
        {
            m.m = glm::translate(m.m, glm::vec3(x, y, z));
        }

        const std::string Translation::Print() const
        {
            std::string output = "Translation: ";
            output += "(" + std::to_string(x) + ";" + std::to_string(y) + ";" + std::to_string(z) + ")";
            return output;
        }


        Rotation::Rotation(const float axis_x_, const float axis_y_, const float axis_z_, const float deg_angle_)
        {
            axis_x = axis_x_;
            axis_y = axis_y_;
            axis_z = axis_z_;
            deg_angle = deg_angle_;
        }

        void Rotation::ApplyTransformation(IMatrix &m) const
        {
            m.m = glm::rotate(m.m, glm::radians(deg_angle), glm::vec3(axis_x, axis_y, axis_z));
        }

        const std::string Rotation::Print() const
        {
            std::string output = "Rotation: ";
            output += "(" + std::to_string(axis_x) + ";" + std::to_string(axis_y) + ";" + std::to_string(axis_z) + ")";
            output += " " + std::to_string(deg_angle);
            return output;
        }

        Scale::Scale(const float axis_x_, const float axis_y_, const float axis_z_)
        {
            axis_x = axis_x_;
            axis_y = axis_y_;
            axis_z = axis_z_;
        }

        void Scale::ApplyTransformation(IMatrix &m) const
        {
            m.m = glm::scale(m.m, glm::vec3(axis_x, axis_y, axis_z));
        }

        const std::string Scale::Print() const
        {
            std::string output = "Scale: ";
            output += "(" + std::to_string(axis_x) + ";" + std::to_string(axis_y) + ";" + std::to_string(axis_z) + ")";
            return output;
        }
    } // Renderer
} // Botcraft
