#include <glad/glad.h>

#include "botcraft/Renderer/Chunk.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        Chunk::Chunk()
        {

        }

        Chunk::~Chunk()
        {

        }

        void Chunk::Update()
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
                glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * face_number, faces_data.data(), GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                buffer_status = BufferStatus::UpToDate;
                break;
            }
            case BufferStatus::Updated:
            {
                std::vector<Face> faces_data(faces.begin(), faces.end());
                face_number = static_cast<unsigned int>(faces_data.size());
                glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * face_number, faces_data.data(), GL_DYNAMIC_DRAW);
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

        void Chunk::AddFace(const Face &f, const std::array<unsigned int, 2>& texture_multipliers,
            const float offset_x, const float offset_y, const float offset_z)
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            if (buffer_status != BufferStatus::Created)
            {
                buffer_status = BufferStatus::Updated;
            }

            Face local_face(f);

            local_face.GetMatrix()[12] += offset_x;
            local_face.GetMatrix()[13] += offset_y;
            local_face.GetMatrix()[14] += offset_z;

            local_face.SetTextureMultipliers(texture_multipliers);

            faces.push_back(std::move(local_face));
        }
    } // Renderer
} // Botcraft
