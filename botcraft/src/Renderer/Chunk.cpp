#include <glad/glad.h>

#include "botcraft/Renderer/Chunk.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        Chunk::Chunk()
        {
            faces_VAO = 0;
            faces_VBO = 0;
            data_VBO = 0;
            face_number = 0;

            buffer_status = BufferStatus::Created;
        }

        Chunk::~Chunk()
        {
            DeleteOpenGLBuffer();
        }

        void Chunk::Update()
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            switch (buffer_status)
            {
            case BufferStatus::Created:
            {
                GenerateOpenGLBuffer();
                std::vector<Face> faces_data(faces_positions.begin(), faces_positions.end());
                face_number = faces_data.size();
                glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * face_number, faces_data.data(), GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                buffer_status = BufferStatus::UpToDate;
                break;
            }
            case BufferStatus::Updated:
            {
                std::vector<Face> faces_data(faces_positions.begin(), faces_positions.end());
                face_number = faces_data.size();
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

        void Chunk::AddFace(const Face &f)
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            if (buffer_status != BufferStatus::Created)
            {
                buffer_status = BufferStatus::Updated;
            }

            auto return_insertion = faces_positions.insert(f);
            if (!return_insertion.second)
            {
                auto it2 = faces_positions.erase(return_insertion.first);
                faces_positions.insert(it2, f);
            }
        }

        void Chunk::RemoveFace(const Face &f)
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            faces_positions.erase(f);
            if (buffer_status != BufferStatus::Created)
            {
                buffer_status = BufferStatus::Updated;
            }
        }

        const unsigned int Chunk::GetNumFace() const
        {
            return face_number;
        }

        void Chunk::Render() const
        {
            glBindVertexArray(faces_VAO);
            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, face_number);
        }

        void Chunk::GenerateOpenGLBuffer()
        {
            glGenVertexArrays(1, &faces_VAO);
            glGenBuffers(1, &faces_VBO);

            //Buffer for the base face (x,y,z)
            glBindVertexArray(faces_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, faces_VBO);
            glBufferData(GL_ARRAY_BUFFER, Face::base_face.size() * sizeof(float), Face::base_face.data(), GL_STATIC_DRAW);

            //(x, y, z) for base face
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

            glGenBuffers(1, &data_VBO);
            glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Face) * face_number, 0, GL_DYNAMIC_DRAW);

            //(matrix4x4) model matrix of the face
            //Actually passed as 4 columns
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void*)0);
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(1, 1);

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void*)(4 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(2, 1);

            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void*)(8 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(3, 1);

            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void*)(12 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(4, 1);

            glEnableVertexAttribArray(5);
            //(atlas_index_col, atlas_index_row, atlas_index_col_overlay, atlas_index_row_overlay) for one face
            glVertexAttribIPointer(5, 2, GL_UNSIGNED_INT, sizeof(Face), (void*)(16 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(5, 1);

            glEnableVertexAttribArray(6);
            //(texture_data) for one face
            glVertexAttribIPointer(6, 1, GL_UNSIGNED_INT, sizeof(Face), (void*)(18 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(6, 1);

            glEnableVertexAttribArray(7);
            //(texture_multiplier, texture_multiplier_overlay) for one face
            glVertexAttribIPointer(7, 2, GL_UNSIGNED_INT, sizeof(Face), (void*)(19 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(7, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void Chunk::DeleteOpenGLBuffer()
        {
            if (faces_VBO)
            {
                glDeleteBuffers(1, &faces_VBO);
            }
            if (data_VBO)
            {
                glDeleteBuffers(1, &data_VBO);
            }
            if (faces_VAO)
            {
                glDeleteVertexArrays(1, &faces_VAO);
            }
        }
    } // Renderer
} // Botcraft