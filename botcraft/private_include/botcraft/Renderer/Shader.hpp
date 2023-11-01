#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

namespace Botcraft
{
    namespace Renderer
    {
        class Shader
        {
        public:
            // constructor reads and builds the shader
            Shader(const std::string& vertexPath = "", const std::string& fragmentPath = "");
            ~Shader();

            const unsigned int Program();

            // use/activate the shader
            void Use();
            // utility uniform functions
            void SetBool(const std::string& name, const bool value) const;
            void SetInt(const std::string& name, const int value) const;
            void SetFloat(const std::string& name, const float value) const;
            void SetMat4(const std::string& name, const glm::mat4& value) const;
            void SetMat3(const std::string& name, const glm::mat3& value) const;
            void SetMat4xN(const std::string& name, const std::vector<glm::mat4>& value) const;
            void SetMat3xN(const std::string& name, const std::vector<glm::mat3>& value) const;
            void SetVec3(const std::string& name, const glm::vec3& value) const;
            void SetVec2(const std::string& name, const glm::vec2& value) const;

        private:
            unsigned int program;
            void CheckCompileErrors(const unsigned int shader, const std::string& type);

            static const std::string default_vertex_shader;
            static const std::string default_fragment_shader;
        };
    } // Renderer
} // Botcraft
