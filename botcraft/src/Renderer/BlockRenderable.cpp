#include <glad/glad.h>

#include "botcraft/Renderer/BlockRenderable.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        BlockRenderable::BlockRenderable()
        {
            faces_VAO = 0;
            faces_VBO = 0;
            data_VBO = 0;
            face_number = 0;

            buffer_status = BufferStatus::Created;
        }

        BlockRenderable::~BlockRenderable()
        {
            DeleteOpenGLBuffer();
        }

        void BlockRenderable::Update()
        {

        }

        void BlockRenderable::ClearFaces()
        {
            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            faces.clear();
            if (buffer_status != BufferStatus::Created)
            {
                buffer_status = BufferStatus::Updated;
            }
        }

        const unsigned int BlockRenderable::GetNumFace() const
        {
            return face_number;
        }

        void BlockRenderable::Render() const
        {
            glBindVertexArray(faces_VAO);
            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, face_number);
        }

        void BlockRenderable::GenerateOpenGLBuffer()
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
            //tex_coords(u0, v0, u1, v1) for one face
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void*)(16 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(5, 1);
            
            glEnableVertexAttribArray(6);
            //tex_coords_overlay(u0, v0, u1, v1) for one face
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Face), (void*)(20 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(6, 1);

            glEnableVertexAttribArray(7);
            //(texture_data) for one face
            glVertexAttribIPointer(7, 1, GL_UNSIGNED_INT, sizeof(Face), (void*)(24 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(7, 1);

            glEnableVertexAttribArray(8);
            //(texture_multiplier, texture_multiplier_overlay) for one face
            glVertexAttribIPointer(8, 2, GL_UNSIGNED_INT, sizeof(Face), (void*)(25 * sizeof(float)));
            //Specify that only one instance of this must be sent to one index
            glVertexAttribDivisor(8, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void BlockRenderable::DeleteOpenGLBuffer()
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