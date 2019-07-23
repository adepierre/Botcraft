#include "botcraft/Renderer/Shader.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
        {
            // 1. retrieve the vertex/fragment source code from filePath
            std::string vertexCode;
            std::string fragmentCode;

            if (!vertexPath.empty())
            {
                std::ifstream vShaderFile;
                std::stringstream vShaderStream;
                vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                try
                {
                    vShaderFile.open(vertexPath);
                    vShaderStream << vShaderFile.rdbuf();
                    vShaderFile.close();
                    vertexCode = vShaderStream.str();
                }
                catch (std::ifstream::failure e)
                {
                    std::cout << "ERROR::SHADER::VERTEX_FILE_NOT_SUCCESFULLY_READ" << std::endl;
                }
            }
            else
            {
                vertexCode = default_vertex_shader;
            }

            if (!fragmentPath.empty())
            {
                std::ifstream fShaderFile;
                fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                try
                {
                    fShaderFile.open(fragmentPath);
                    std::stringstream fShaderStream;
                    fShaderStream << fShaderFile.rdbuf();
                    fShaderFile.close();
                    fragmentCode = fShaderStream.str();
                }
                catch (std::ifstream::failure e)
                {
                    std::cout << "ERROR::SHADER::FRAGMENT_FILE_NOT_SUCCESFULLY_READ" << std::endl;
                }
            }
            else
            {
                fragmentCode = default_fragment_shader;
            }

            const char *vShaderCode = vertexCode.c_str();
            const char *fShaderCode = fragmentCode.c_str();

            // 2. compile shaders
            unsigned int vertex, fragment;

            // vertex shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            CheckCompileErrors(vertex, "VERTEX");

            // fragment Shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            CheckCompileErrors(fragment, "FRAGMENT");

            // shader Program
            program = glCreateProgram();
            glAttachShader(program, vertex);
            glAttachShader(program, fragment);
            glLinkProgram(program);
            CheckCompileErrors(program, "PROGRAM");

            // delete the shaders as they're linked into our program now and no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        Shader::~Shader()
        {
            glDeleteProgram(program);
        }

        const unsigned int Shader::Program()
        {
            return program;
        }

        // use/activate the shader
        void Shader::Use()
        {
            glUseProgram(program);
        }

        // utility uniform functions
        void Shader::SetBool(const std::string &name, const bool value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniform1i(loc, (int)value);
        }

        void Shader::SetInt(const std::string &name, const int value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniform1i(loc, value);
        }

        void Shader::SetFloat(const std::string &name, const float value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniform1f(loc, value);
        }

        void Shader::SetMat4(const std::string &name, const glm::mat4 &value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        }

        void Shader::SetMat3(const std::string &name, const glm::mat3 &value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        }

        void Shader::SetMat4xN(const std::string & name, const std::vector<glm::mat4> &value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniformMatrix4fv(loc, (int)value.size(), GL_FALSE, glm::value_ptr(value[0]));
        }

        void Shader::SetMat3xN(const std::string &name, const std::vector<glm::mat3> &value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniformMatrix3fv(loc, (int)value.size(), GL_FALSE, glm::value_ptr(value[0]));
        }

        void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniform3f(loc, value[0], value[1], value[2]);
        }

        void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
        {
            unsigned int loc = glGetUniformLocation(program, name.c_str());
            glUniform2f(loc, value[0], value[1]);
        }

        void Shader::CheckCompileErrors(const unsigned int shader, const std::string &type)
        {
            int success;
            char infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
        }

        const std::string Shader::default_vertex_shader =
            "#version 330 core\n"
            "\n"
            "layout (location = 0) in vec3 aPos;\n"
            "//This matrix is actually four columns\n"
            "layout (location = 1) in mat4 aModel;\n"
            "//layout (location = 2) in vec4 aModelCol1;\n"
            "//layout (location = 3) in vec4 aModelCol2;\n"
            "//layout (location = 4) in vec4 aModelCol3;\n"
            "layout (location = 5) in uvec2 atlas_index;\n"
            "layout (location = 6) in uint texture_data;\n"
            "layout (location = 7) in uvec2 texture_multiplier;\n"
            "\n"
            "layout (std140) uniform MatriceView\n"
            "{\n"
            "\tmat4 view;\n"
            "};\n"
            "\n"
            "uniform mat4 projection;\n"
            "\n"
            "out vec2 TexCoord;\n"
            "out vec2 AtlasCoord;\n"
            "out vec2 AtlasCoord_overlay;\n"
            "flat out uint BackFaceDisplay;\n"
            "flat out uint UseOverlay;\n"
            "flat out vec4 TextureMultiplier;\n"
            "flat out vec4 TextureMultiplier_overlay;\n"
            "\n"
            "void main()\n"
            "{\n"
            "\t//mat4 aModel;\n"
            "\t//aModel[0] = aModelCol0;\n"
            "\t//aModel[1] = aModelCol1;\n"
            "\t//aModel[2] = aModelCol2;\n"
            "\t//aModel[3] = aModelCol3;\n"
            "\tgl_Position = projection * view * (aModel * vec4(aPos, 1.0));\n"
            "\n"
            "\tint vertex_id = gl_VertexID;\n"
            "\n"
            "\tint rotation = int(texture_data >> 21) & 0x03;\n"
            "\n"
            "\tint rotated_indices[4] = int[4](1, 3, 0, 2);\n"
            "\tfor(int i = 0; i < rotation; ++i)\n"
            "\t{\n"
            "\t\tvertex_id = rotated_indices[vertex_id];\n"
            "\t}\n"
            "\n"
            "\tTexCoord = vec2((texture_data >> (int(vertex_id % 2) * 5 + 10)) & uint(0x1F), (texture_data >> (int(vertex_id > 1) * 5)) & uint(0x1F)) / 16.0;\n"
            "\n"
            "\tAtlasCoord = vec2(float(atlas_index[0] & uint(0xFF)), float(atlas_index[0] >> 16));\n"
            "\tAtlasCoord_overlay = vec2(float(atlas_index[1] & uint(0xFF)), float(atlas_index[1] >> 16));\n"
            "\n"
            "\tBackFaceDisplay = uint((texture_data >> 20) & uint(0x01));\n"
            "\tUseOverlay = uint((texture_data >> 23) & uint(0x01));\n"
            "\tTextureMultiplier = vec4(float(texture_multiplier[0] & uint(0xFF)), float((texture_multiplier[0] >> 8) & uint(0xFF)), float((texture_multiplier[0] >> 16) & uint(0xFF)), float((texture_multiplier[0] >> 24) & uint(0xFF))) / 255.0f;\n"
            "\tTextureMultiplier_overlay = vec4(float(texture_multiplier[1] & uint(0xFF)), float((texture_multiplier[1] >> 8) & uint(0xFF)), float((texture_multiplier[1] >> 16) & uint(0xFF)), float((texture_multiplier[1] >> 24) & uint(0xFF))) / 255.0f;\n"
            "}";

        const std::string Shader::default_fragment_shader =
            "#version 330 core\n"
            "\n"
            "in vec2 TexCoord;\n"
            "in vec2 AtlasCoord;\n"
            "in vec2 AtlasCoord_overlay;\n"
            "flat in uint BackFaceDisplay;\n"
            "flat in uint UseOverlay;\n"
            "flat in vec4 TextureMultiplier;\n"
            "flat in vec4 TextureMultiplier_overlay;\n"
            "\n"
            "uniform vec2 atlas_dim;\n"
            "\n"
            "uniform sampler2D atlas_texture;\n"
            "\n"
            "out vec4 FragColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "\tif(!bool(BackFaceDisplay )&& !gl_FrontFacing)\n"
            "\t{\n"
            "\t\tdiscard;\n"
            "\t}\n"
            "\n"
            "if(!bool(UseOverlay))\n"
            "{\n"
            "\tFragColor = TextureMultiplier * texture(atlas_texture, (AtlasCoord + TexCoord) / atlas_dim);\n"
            "}\n"
            "else\n"
            "{\n"
            "\tvec4 base_color = TextureMultiplier * texture(atlas_texture, (AtlasCoord + TexCoord) / atlas_dim);\n"
            "\tvec4 overlay_color = TextureMultiplier_overlay * texture(atlas_texture, (AtlasCoord_overlay + TexCoord) / atlas_dim);\n"
            "\tfloat alpha = overlay_color[3] + base_color[3] * (1.0f - overlay_color[3]);\n"
            "FragColor = vec4((vec3(overlay_color) * overlay_color[3] + (1.0f - overlay_color[3]) * vec3(base_color) * base_color[3]) / alpha, alpha);\n"
            "}\n"
            "\n"
            "\tif(FragColor.a < 0.1)\n"
            "\t{\n"
            "\t\tdiscard;\n"
            "\t}\n"
            "}";
    } // Renderer
} // Botcraft