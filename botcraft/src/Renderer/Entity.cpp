#include "botcraft/Renderer/Entity.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        Entity::Entity(const std::vector<Face>& faces_)
        {
            SetFaces(std::vector<Face>(faces_.begin(), faces_.end()));
        }

        Entity::~Entity()
        {

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
