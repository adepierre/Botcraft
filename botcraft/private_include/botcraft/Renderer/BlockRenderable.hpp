#pragma once

#include <mutex>
#include <vector>

#include "botcraft/Renderer/Face.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        class BlockRenderable
        {
        public:
            BlockRenderable();
            virtual ~BlockRenderable();

            BlockRenderable(const BlockRenderable&) = delete;
            BlockRenderable& operator=(const BlockRenderable&) = delete;

            void SetFaces(std::vector<Face>&& faces_);
            void Update();
            void ClearFaces();
            const unsigned int GetNumFace() const;
            void Render() const;

        protected:
            void GenerateOpenGLBuffer();
            void DeleteOpenGLBuffer();

            // Called with mutex_faces held, after the GPU buffer is current.
            virtual void OnUploadedLocked();

        protected:
            unsigned int faces_VAO;
            unsigned int faces_VBO;
            unsigned int data_VBO;
            unsigned int face_number;

            std::vector<Face> faces;
            bool dirty;

            std::mutex mutex_faces;
        };
    } // Renderer
} // Botcraft
