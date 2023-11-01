#include "botcraft/Renderer/Camera.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        Camera::Camera(glm::vec3 position_, glm::vec3 up_, float yaw_, float pitch_)
        {
            position = position_;
            worldUp = up_;
            yaw = yaw_;
            pitch = pitch_;
            UpdateCameraViewMatrix();
        }

        const glm::mat4& Camera::GetViewMatrix() const
        {
            return view_matrix;
        }

        const float Camera::GetDistance(const float x_, const float y_, const float z_) const
        {
            float delta_x = position.x - x_;
            float delta_y = position.y - y_;
            float delta_z = position.z - z_;

            return delta_x * delta_x + delta_y * delta_y + delta_z * delta_z;
        }

        void Camera::SetPosition(const float x, const float y, const float z)
        {
            glm::vec3 new_pos(x, y, z);
            has_changed_position = has_changed_position || new_pos != position;
            position = new_pos;
            UpdateCameraViewMatrix();
        }

        const glm::vec3& Camera::GetPosition() const
        {
            return position;
        }

        const glm::vec3& Camera::GetFront() const
        {
            return front;
        }

        const std::array<glm::vec4, 6>& Camera::GetFrustumPlanes() const
        {
            return frustum;
        }

        const float Camera::GetYaw() const
        {
            return yaw;
        }

        const float Camera::GetPitch() const
        {
            return pitch;
        }

        void Camera::SetRotation(const float pitch_, const float yaw_)
        {
            has_changed_orientation = has_changed_orientation || pitch != pitch_ || yaw != yaw_;
            pitch = pitch_;
            yaw = yaw_;
            while (yaw >= 180.0f)
            {
                yaw -= 360.0f;
            }
            while (yaw < -180.0f)
            {
                yaw += 360.0f;
            }
            UpdateCameraViewMatrix();
        }

        void Camera::SetProjection(const glm::mat4& projection)
        {
            projection_matrix = projection;
            ComputeFrustumPlanes();
        }

        bool Camera::GetHasChangedPosition() const
        {
            return has_changed_position;
        }

        bool Camera::GetHasChangedOrientation() const
        {
            return has_changed_orientation;
        }

        void Camera::ResetHasChangedPosition()
        {
            has_changed_position = false;
        }

        void Camera::ResetHasChangedOrientation()
        {
            has_changed_orientation = false;
        }

        void Camera::UpdateCameraViewMatrix()
        {
            // Calculate the front, right and up vectors
            front.x = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = -sin(glm::radians(pitch));
            front.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(front);

            // Calculate up vector needed for view matrix
            const glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
            const glm::vec3 up = glm::normalize(glm::cross(right, front));

            view_matrix = glm::lookAt(position, position + front, up);
            ComputeFrustumPlanes();
        }

        void Camera::ComputeFrustumPlanes()
        {
            const glm::mat4 clip_matrix = glm::transpose(projection_matrix * view_matrix);

            // Compute the planes
            frustum[0] = clip_matrix[3] - clip_matrix[0]; // right
            frustum[1] = clip_matrix[3] + clip_matrix[0]; // left
            frustum[2] = clip_matrix[3] + clip_matrix[1]; // bottom
            frustum[3] = clip_matrix[3] - clip_matrix[1]; // top
            frustum[4] = clip_matrix[3] + clip_matrix[2]; // near
            frustum[5] = clip_matrix[3] - clip_matrix[2]; // far

            // We do not need normalization for our usecase
        }
    } // Renderer
} // Botcraft