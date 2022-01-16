#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "botcraft/Renderer/TransparentChunk.hpp"

#include <algorithm>

namespace Botcraft
{
    namespace Renderer
    {
        const float Distance(const Face &f, const glm::vec3 &pos)
        {
            const glm::vec3 center = glm::make_mat4(f.GetMatrix().data()) * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

            const float delta_x = pos.x - center.x;
            const float delta_y = pos.y - center.y;
            const float delta_z = pos.z - center.z;

            return delta_x * delta_x + delta_y * delta_y + delta_z * delta_z;
        }

        TransparentChunk::TransparentChunk()
        {
            display_buffer_status = BufferStatus::UpToDate;
        }

        TransparentChunk::~TransparentChunk()
        {

        }

        void TransparentChunk::Update()
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            switch (buffer_status)
            {
            case BufferStatus::Created:
            {
                GenerateOpenGLBuffer();
                display_faces_positions = std::vector<Face>(faces.begin(), faces.end());
                face_number = display_faces_positions.size();
                glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * face_number, display_faces_positions.data(), GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                buffer_status = BufferStatus::UpToDate;
                display_buffer_status = BufferStatus::Updated;
                break;
            }
            case BufferStatus::Updated:
            {
                display_faces_positions = std::vector<Face>(faces.begin(), faces.end());
                face_number = display_faces_positions.size();
                display_buffer_status = BufferStatus::Updated;
                glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * face_number, display_faces_positions.data(), GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                if (face_number == 0)
                {
                    DeleteOpenGLBuffer();
                    buffer_status = BufferStatus::Created;
                }
                else
                {
                    buffer_status = BufferStatus::UpToDate;
                }
                break;
            }
            case BufferStatus::UpToDate:
                break;
            default:
                break;
            }
        }

        void TransparentChunk::SetDisplayStatus(const BufferStatus s)
        {
            display_buffer_status = s;
        }

        void TransparentChunk::Sort(const glm::vec3 &cam_pos)
        {
            if (display_buffer_status == BufferStatus::UpToDate)
            {
                return;
            }

            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            std::sort(display_faces_positions.begin(), display_faces_positions.end(), [this, cam_pos](const Face &f1, const Face &f2){return Distance(f1, cam_pos) > Distance(f2, cam_pos); });


            glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Face) * display_faces_positions.size(), display_faces_positions.data());
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            display_buffer_status = BufferStatus::UpToDate;
        }
    } // Renderer
} // Botcraft