#pragma once

#include <deque>
#include <mutex>

#include "botcraft/Renderer/Face.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        // Status of a face buffer
        enum class BufferStatus
        {
            Created,  // The buffer is new, must be created in OpenGL
            Updated,  // The existing buffer has been updated
            UpToDate, // The OpenGL buffer is up to date
        };

        class BlockRenderable
        {
        public:
            BlockRenderable();
            ~BlockRenderable();

            void Update();
            void ClearFaces();
            const unsigned int GetNumFace() const;
            void Render() const;

        protected:
            void GenerateOpenGLBuffer();
            void DeleteOpenGLBuffer();

        protected:
            unsigned int faces_VAO;
            unsigned int faces_VBO;
            unsigned int data_VBO;
            unsigned int face_number;

            std::deque<Face> faces;

            BufferStatus buffer_status;

            std::mutex mutex_faces;
        };
    } // Renderer
} // Botcraft