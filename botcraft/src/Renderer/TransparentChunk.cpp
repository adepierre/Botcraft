#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "botcraft/Renderer/TransparentChunk.hpp"

#include <algorithm>

namespace Botcraft
{
    namespace Renderer
    {
        namespace
        {
            float Distance(const Face& f, const glm::vec3& pos)
            {
                const glm::vec3 center = glm::make_mat4(f.GetMatrix().data()) * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

                const float delta_x = pos.x - center.x;
                const float delta_y = pos.y - center.y;
                const float delta_z = pos.z - center.z;

                return delta_x * delta_x + delta_y * delta_y + delta_z * delta_z;
            }
        }

        TransparentChunk::TransparentChunk()
        {
            needs_sort = false;
        }

        TransparentChunk::~TransparentChunk()
        {

        }

        void TransparentChunk::MarkForSort()
        {
            needs_sort = true;
        }

        void TransparentChunk::Sort(const glm::vec3& cam_pos)
        {
            if (!needs_sort.load())
            {
                return;
            }

            std::lock_guard<std::mutex> lock_faces(mutex_faces);
            // Re-check under the lock. If MarkForSort/OnUploaded set the flag
            // while we waited, exchange returns true and we sort now.
            if (!needs_sort.exchange(false))
            {
                return;
            }

            if (display_faces_positions.empty())
            {
                return;
            }

            std::sort(display_faces_positions.begin(), display_faces_positions.end(), [this, cam_pos](const Face& f1, const Face& f2) { return Distance(f1, cam_pos) > Distance(f2, cam_pos); });

            glBindBuffer(GL_ARRAY_BUFFER, data_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Face) * display_faces_positions.size(), display_faces_positions.data());
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void TransparentChunk::OnUploadedLocked()
        {
            display_faces_positions = faces;
            needs_sort = true;
        }
    } // Renderer
} // Botcraft
