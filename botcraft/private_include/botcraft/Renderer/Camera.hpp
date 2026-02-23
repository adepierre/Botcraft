#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>

namespace Botcraft
{
    namespace Renderer
    {
        // A camera class that keep position and orientation and calculates the corresponding matrices for OpenGL
        class Camera
        {
        public:
            // Constructor
            Camera(glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f), float yaw_ = 0.0f, float pitch_ = 0.0f);

            // Getter
            const glm::mat4& GetViewMatrix() const;
            const glm::vec3& GetPosition() const;
            const glm::vec3& GetFront() const;
            const std::array<glm::vec4, 6>& GetFrustumPlanes() const;
            float GetYaw() const;
            float GetPitch() const;

            // Setter
            void SetPosition(const float x, const float y, const float z);
            void SetRotation(const float pitch_, const float yaw_);
            void SetProjection(const glm::mat4& projection);

            bool GetHasChangedPosition() const;
            bool GetHasChangedOrientation() const;

            void ResetHasChangedPosition();
            void ResetHasChangedOrientation();

            // Returns the distance between coordinates and the camera
            float GetDistance(const float x_, const float y_, const float z_) const;

        private:
            // Compute the view matrix from camera parameters
            void UpdateCameraViewMatrix();

            // Compute frustum planes from camera parameters
            void ComputeFrustumPlanes();

        private:
            glm::vec3 worldUp;

            // Camera position
            glm::vec3 position;
            glm::vec3 front;

            // Camera orientation
            float yaw;
            float pitch;

            // Matrices
            glm::mat4 projection_matrix;
            glm::mat4 view_matrix;

            // Frustum planes
            std::array<glm::vec4, 6> frustum;

            bool has_changed_position    { false };
            bool has_changed_orientation { false };
        };
    } // Renderer
} // Botcraft
