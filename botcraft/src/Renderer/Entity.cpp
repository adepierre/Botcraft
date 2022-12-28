#include <glad/glad.h>

#include "botcraft/Renderer/Entity.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        Entity::Entity(const std::vector<Face>& faces_)
        {
            faces = std::deque<Face>(faces_.begin(), faces_.end());
            face_number = static_cast<unsigned int>(faces.size());
        }

        Entity::~Entity()
        {

        }

        void Entity::Update()
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            switch (buffer_status)
            {
            case BufferStatus::Created:
            {
                GenerateOpenGLBuffer();
                std::vector<Face> faces_data(faces.begin(), faces.end());
                face_number = static_cast<unsigned int>(faces_data.size());
                glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Face) * face_number, faces_data.data());
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                buffer_status = BufferStatus::UpToDate;
                break;
            }
            case BufferStatus::Updated:
            {
                std::vector<Face> faces_data(faces.begin(), faces.end());
                face_number = static_cast<unsigned int>(faces_data.size());
                glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Face) * face_number, faces_data.data());
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

        void Entity::UpdateFaces(const std::vector<Face> &faces_)
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            if (buffer_status != BufferStatus::Created)
            {
                buffer_status = BufferStatus::Updated;
            }

            faces = std::deque<Face>(faces_.begin(), faces_.end());
        }

        Vector3<float> Entity::GetApproxPos()
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            if (faces.size() == 0)
            {
                return Vector3<float>();
            }

            return Vector3<float>(
                    faces[0].GetMatrix()[12],
                    faces[0].GetMatrix()[13],
                    faces[0].GetMatrix()[14]
                );
        }
    } // Renderer
} // Botcraft
