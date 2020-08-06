#include "botcraft/Renderer/CubeWorldRenderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_set>

#ifdef USE_IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
static bool imgui_demo = false;
#endif

#include "botcraft/Renderer/Atlas.hpp"
#include "botcraft/Renderer/Camera.hpp"
#include "botcraft/Renderer/Shader.hpp"
#include "botcraft/Renderer/Chunk.hpp"
#include "botcraft/Renderer/ImageSaver.hpp"
#include "botcraft/Renderer/TransparentChunk.hpp"

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/World/Chunk.hpp"

const std::vector<float> color_day({ 0.6f, 0.85f, 0.9f });
const std::vector<float> color_night({0.1f, 0.1f, 0.1f});

namespace Botcraft
{
    namespace Renderer
    {
        CubeWorldRenderer::CubeWorldRenderer(const unsigned int &window_width, const unsigned int &window_height,
            const std::vector<std::pair<std::string, std::string> > &textures_path_names,
            const unsigned int section_height_, const bool headless_)
        {
            mouse_last_x = window_width / 2.0f;
            mouse_last_y = window_height / 2.0f;
            first_mouse = true;

            headless = headless_;

            faces_should_be_updated = true;

            chunks = std::unordered_map<Position, std::shared_ptr<Chunk> >();
            transparent_chunks = std::unordered_map<Position, std::shared_ptr<TransparentChunk> >();

            deltaTime = 0.0f;
            lastFrameTime = 0.0f;

            current_window_width = window_width;
            current_window_height = window_height;
            has_proj_changed = true;

            MouseCallback = [](double, double) {};
            KeyboardCallback = [](std::array<bool, (int)KEY_CODE::NUMBER_OF_KEYS>, float) {};

            section_height = section_height_;

            //Build atlas
            atlas = std::shared_ptr<Atlas>(new Atlas);
            atlas->LoadData(textures_path_names);

            take_screenshot = false;

            day_time = 0.0f;

            camera = std::unique_ptr<Camera>(new Camera);

            rendering_thread = std::thread(&CubeWorldRenderer::Run, this);
        }

        CubeWorldRenderer::~CubeWorldRenderer()
        {
            if (rendering_thread.joinable())
            {
                rendering_thread.join();
            }
        }

        void CubeWorldRenderer::Run()
        {
            if (!Init())
            {
                return;
            }

            my_shader->Use();

            while (!glfwWindowShouldClose(window))
            {
                double currentFrame = glfwGetTime();
                auto now = std::chrono::system_clock::now();

                //Max 60 FPS
                auto end = now + std::chrono::microseconds(1000000 / 60);

                deltaTime = currentFrame - lastFrameTime;
                lastFrameTime = currentFrame;

                InternalProcessInput(window);

#ifdef USE_IMGUI
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                if (imgui_demo)
                {
                    ImGui::ShowDemoWindow(&imgui_demo);
                }

                {
                    ImGui::SetNextWindowPos(ImVec2(0, 0));
                    ImGui::SetNextWindowSize(ImVec2(290, 70));
                    ImGui::Begin("Position");
                    ImGui::Text("%f, %f, %f", camera->GetPosition().x, camera->GetPosition().y - 1.62f, camera->GetPosition().z);
                    ImGui::Text("Yaw: %f  ||  ", camera->GetYaw());
                    ImGui::SameLine();
                    ImGui::Text("Pitch: %f", camera->GetPitch());
                    ImGui::End();
                }
                {
                    ImGui::SetNextWindowPos(ImVec2(0, 75));
                    ImGui::SetNextWindowSize(ImVec2(290, 70));
                    ImGui::Begin("Targeted cube");
                    Position raycasted_pos;
                    Position raycasted_normal;
                    std::shared_ptr<Blockstate> raycasted_blockstate;
                    {
                        /*std::lock_guard<std::mutex> world_guard(world_mutex);
                        raycasted_blockstate =
                            rendered_world->Raycast(Vector3<double>(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z),
                            Vector3<double>(camera->GetFront().x, camera->GetFront().y, camera->GetFront().z),
                            6.0f, raycasted_pos, raycasted_normal);*/
                    }
                    if (raycasted_blockstate)
                    {
                        ImGui::Text("Watching block at %i, %i, %i", raycasted_pos.x, raycasted_pos.y, raycasted_pos.z);
                        ImGui::Text((std::string("Block: ") + raycasted_blockstate->GetName()).c_str());
                    }
                    else
                    {
                        ImGui::Text("Watching block at");
                        ImGui::Text("Block: ");
                    }
                    ImGui::End();
                }
#endif
                const float current_day_time = day_time;
                std::vector<float> current_color(3);
                for (int i = 0; i < 3; ++i)
                {
                    current_color[i] = 2.0f * ((0.5f - std::abs(current_day_time - 0.5f)) * color_day[i] + (0.5f - std::min(std::abs(1.0f - current_day_time), current_day_time)) * color_night[i]);
                }
                glClearColor(current_color[0], current_color[1], current_color[2], 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //Change view matrix
                if (camera->GetHasChangedOrientation() || camera->GetHasChangedPosition())
                {
                    m_mutex_camera.lock();
                    glm::mat4 view_matrix = camera->GetViewMatrix();
                    if (camera->GetHasChangedPosition())
                    {
                        transparent_chunks_mutex.lock();
                        for (auto it = transparent_chunks.begin(); it != transparent_chunks.end(); ++it)
                        {
                            it->second->SetDisplayStatus(BufferStatus::Updated);
                        }
                        transparent_chunks_mutex.unlock();
                    }
                    camera->ResetHasChangedPosition();
                    camera->ResetHasChangedOrientation();
                    m_mutex_camera.unlock();
                    glBindBuffer(GL_UNIFORM_BUFFER, view_uniform_buffer);
                    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view_matrix));
                    glBindBuffer(GL_UNIFORM_BUFFER, 0);
                }

                if (has_proj_changed)
                {
                    glm::mat4 projection = glm::perspective(glm::radians(45.0f), current_window_width / (float)current_window_height, 0.1f, 200.0f);
                    my_shader->SetMat4("projection", projection);
                    m_mutex_camera.lock();
                    camera->SetProjection(projection);
                    m_mutex_camera.unlock();
                    has_proj_changed = false;
                }

                if (faces_should_be_updated)
                {
                    faces_should_be_updated = false;
                    chunks_mutex.lock();
                    for (auto it = chunks.begin(); it != chunks.end();)
                    {
                        it->second->Update();
                        if (it->second->GetNumFace() == 0)
                        {
                            it = chunks.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                    chunks_mutex.unlock();
                    transparent_chunks_mutex.lock();
                    for (auto it = transparent_chunks.begin(); it != transparent_chunks.end();)
                    {
                        it->second->Update();
                        if (it->second->GetNumFace() == 0)
                        {
                            it = transparent_chunks.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                    transparent_chunks_mutex.unlock();
                }

                my_shader->Use();

                glBindTexture(GL_TEXTURE_2D, atlas_texture);

                //Draw all faces
                RenderFaces();

                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);

#ifdef USE_IMGUI
                ImGui::Render();

                // Render ImGui
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
                glfwSwapBuffers(window);
                glfwPollEvents();

                if (take_screenshot)
                {
                    std::vector<unsigned char> pixels(current_window_height * current_window_width * 3);
                    glReadPixels(0, 0, current_window_width, current_window_height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

                    WriteImage(screenshot_path, current_window_height, current_window_width, 3, pixels.data(), true);
                    take_screenshot = false;
                }

                //Wait to have 60 FPS
                std::this_thread::sleep_until(end);
            }

            chunks.clear();
            transparent_chunks.clear();

            glDeleteTextures(1, &atlas_texture);

            my_shader.reset();
            camera.reset();

#ifdef USE_IMGUI
            // ImGui cleaning
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
#endif

            glfwDestroyWindow(window);
            glfwTerminate();
        }

        void CubeWorldRenderer::Close()
        {
            glfwSetWindowShouldClose(window, true);
        }

        void CubeWorldRenderer::UpdateChunk(const int x_, const int z_, const std::shared_ptr<const Botcraft::Chunk> chunk)
        {
            // Remove any previous version of this chunk
            {
                std::lock_guard<std::mutex> lock(chunks_mutex);
                Position pos(x_, 0, z_);
                for (int y = 0; y < CHUNK_HEIGHT / section_height; ++y)
                {
                    pos.y = y;
                    auto it = chunks.find(pos);
                    if (it != chunks.end())
                    {
                        it->second->ClearFaces();
                    }
                }
            }
            {
                std::lock_guard<std::mutex> lock(transparent_chunks_mutex);
                Position pos(x_, 0, z_);
                for (int y = 0; y < CHUNK_HEIGHT / CHUNK_WIDTH; ++y)
                {
                    pos.y = y; 
                    auto it = transparent_chunks.find(pos);
                    if (it != transparent_chunks.end())
                    {
                        it->second->ClearFaces();
                    }
                }
            }

            if (chunk == nullptr)
            {
                return;
            }

            auto& AssetsManager_ = AssetsManager::getInstance();

            // For each block in the chunk, check its neighbours
            // to see which face to draw
            const std::vector<Position> neighbour_positions({ Position(0, -1, 0), Position(0, 0, -1),
                            Position(-1, 0, 0), Position(1, 0, 0), Position(0, 0, 1), Position(0, 1, 0) });

            std::vector<std::shared_ptr<Blockstate> > neighbour_blockstates(6);
            std::vector<unsigned char> neighbour_model_ids(6);

            Position pos;
            for (int y = 0; y < CHUNK_HEIGHT; ++y)
            {
                pos.y = y;
                for (int z = 0; z < CHUNK_WIDTH; ++z)
                {
                    pos.z = z;
                    for (int x = 0; x < CHUNK_WIDTH; ++x)
                    {
                        pos.x = x;
                        
                        // If this block is air, just skip it
                        const Block* this_block = chunk->GetBlock(pos);
                        if (this_block == nullptr ||
                            this_block->GetBlockstate()->IsAir())
                        {
                            continue;
                        }

                        // Else check its neighbours to find which face to draw
                        for (int i = 0; i < 6; ++i)
                        {
                            const Block* neighbour_block = chunk->GetBlock(pos + neighbour_positions[i]);
                            if (neighbour_block == nullptr)
                            {
                                neighbour_blockstates[i] = nullptr;
                                neighbour_model_ids[i] = 0;
                            }
                            else
                            {
                                neighbour_blockstates[i] = neighbour_block->GetBlockstate();
                                neighbour_model_ids[i] = neighbour_block->GetModelId();
                            }
                        }

                        //Check if this block is sourrounded by non transparent blocks
                        for (int i = 0; i < neighbour_positions.size(); ++i)
                        {
                            if (neighbour_blockstates[i] == nullptr || 
                                neighbour_blockstates[i]->IsTransparent())
                            {
                                break;
                            }

                            //If we are here, all the neigbhours are non transparent blocks, so
                            //there is no face to add to the renderer
                            if (i == neighbour_positions.size() - 1)
                            {
                                continue;
                            }
                        }
                        
                        //Add all faces of the current state
                        const std::vector<FaceDescriptor>& current_faces = this_block->GetBlockstate()->GetModel(this_block->GetModelId()).GetFaces();
#if PROTOCOL_VERSION < 358
                        const std::shared_ptr<Biome> current_biome = AssetsManager_.GetBiome(chunk->GetBiome(x, z));
#else
                        const std::shared_ptr<Biome> current_biome = AssetsManager_.GetBiome(chunk->GetBiome(x, y, z));
#endif

                        for (int i = 0; i < current_faces.size(); ++i)
                        {
                            //Check if the neighbour in this direction is hidding this face
                            // We also remove the faces between two transparent blocks with the same names
                            // (example: faces between two water blocks)
                            if (current_faces[i].cullface_direction == Orientation::None ||
                                !neighbour_blockstates[(int)current_faces[i].cullface_direction] ||
                                (neighbour_blockstates[(int)current_faces[i].cullface_direction]->IsTransparent() &&
                                    neighbour_blockstates[(int)current_faces[i].cullface_direction]->GetName() != this_block->GetBlockstate()->GetName())
                                )
                            {
                                AddFace(pos.x + CHUNK_WIDTH * x_, pos.y, pos.z + CHUNK_WIDTH * z_, 
                                    current_faces[i].face, current_faces[i].texture_names, 
                                    GetColorModifier(pos.y, current_biome, this_block->GetBlockstate(),
                                        current_faces[i].use_tintindexes));
                            }
                        }
                    }
                }
            }
        }

        void CubeWorldRenderer::AddFace(const int x_, const int y_, const int z_, const Face &face_,
                                        const std::vector<std::string> &texture_identifiers_,
                                        const std::vector<unsigned int> &texture_multipliers_)
        {
            std::array<unsigned short, 4> atlas_pos = { 0 };
            std::array<unsigned short, 4> atlas_size = { 0 };
            std::array<Transparency, 2> transparencies = { Transparency::Opaque };
            std::array<Animation, 2> animated = { Animation::Static };
            
            for (int i = 0; i < std::min(2, (int)texture_identifiers_.size()); ++i)
            {
                const std::pair<int, int> &atlas_coords = atlas->GetPosition(texture_identifiers_[i]);
                atlas_pos[2 * i + 0] = atlas_coords.first;
                atlas_pos[2 * i + 1] = atlas_coords.second;
                const std::pair<int, int>& atlas_dims = atlas->GetSize(texture_identifiers_[i]);
                atlas_size[2 * i + 0] = atlas_dims.first;
                atlas_size[2 * i + 1] = atlas_dims.second;
                transparencies[i] = atlas->GetTransparency(texture_identifiers_[i]);
                animated[i] = atlas->GetAnimation(texture_identifiers_[i]);
            }

            std::array<unsigned int, 2> texture_multipliers = { 0xFFFFFFFF };
            for (int i = 0; i < std::min(2, (int)texture_multipliers_.size()); ++i)
            {
                texture_multipliers[i] = texture_multipliers_[i];
            }

            Face face(face_);
            face.SetTextureMultipliers(texture_multipliers);
            
            std::array<float, 4> coords = face.GetTextureCoords(false);
            unsigned short height_normalizer = animated[0] == Animation::Animated ? atlas_size[0] : atlas_size[1];
            for (int i = 0; i < 2; ++i)
            {
                coords[2 * i + 0] = (atlas_pos[0] + coords[2 * i + 0] / 16.0f * atlas_size[0]) / atlas->GetWidth();
                coords[2 * i + 1] = (atlas_pos[1] + coords[2 * i + 1] / 16.0f * height_normalizer) / atlas->GetHeight();
            }
            face.SetTextureCoords(coords, false);

            if (texture_identifiers_.size() > 1)
            {
                coords = face.GetTextureCoords(true); 
                height_normalizer = animated[1] == Animation::Animated ? atlas_size[2] : atlas_size[3];
                for (int i = 0; i < 2; ++i)
                {
                    coords[2 * i + 0] = (atlas_pos[2] + coords[2 * i + 0] / 16.0f * atlas_size[2]) / atlas->GetWidth();
                    coords[2 * i + 1] = (atlas_pos[3] + coords[2 * i + 1] / 16.0f * height_normalizer) / atlas->GetHeight();
                }
                face.SetTextureCoords(coords, true);
            }

            //Add 0.5 because the origin of the block is at the center
            //but the coordinates start from the block corner
            face.GetMatrix()[12] += x_ + 0.5f;
            face.GetMatrix()[13] += y_ + 0.5f;
            face.GetMatrix()[14] += z_ + 0.5f;

            const Transparency transparency = transparencies[0];
            if (transparency == Transparency::Opaque)
            {
                face.SetDisplayBackface(false);
            }

            const Position position((int)floor(x_ / (double)CHUNK_WIDTH), (int)floor(y_ / (double)section_height), (int)floor(z_ / (double)CHUNK_WIDTH));

            if (transparency == Transparency::Partial)
            {
                std::lock_guard<std::mutex> lock(transparent_chunks_mutex);
                auto chunk_it = transparent_chunks.find(position);
                if (chunk_it == transparent_chunks.end())
                {
                    transparent_chunks[position] = std::shared_ptr<TransparentChunk>(new TransparentChunk);
                }
                transparent_chunks[position]->AddFace(face);
            }
            else
            {
                std::lock_guard<std::mutex> lock(chunks_mutex);
                auto chunk_it = chunks.find(position);
                if (chunk_it == chunks.end())
                {
                    chunks[position] = std::shared_ptr<Chunk>(new Chunk);
                }
                chunks[position]->AddFace(face);
            }
        }

        const std::vector<unsigned int> CubeWorldRenderer::GetColorModifier(const int y, const std::shared_ptr<Biome> biome, const std::shared_ptr<Blockstate> blockstate, const std::vector<bool> &use_tintindex) const
        {
            std::vector<unsigned int> texture_modifier(use_tintindex.size(), 0xFFFFFFFF);
            for (int i = 0; i < use_tintindex.size(); ++i)
            {
                switch (blockstate->GetTintType())
                {
                case TintType::None:
                    break;
                case TintType::Grass:
                    if (use_tintindex[i])
                    {
                        if (biome)
                        {
                            texture_modifier[i] = biome->GetColorMultiplier(y, true);
                        }
                    }
                    break;
                case TintType::Leaves:
                    if (use_tintindex[i])
                    {
                        if (biome)
                        {
                            texture_modifier[i] = biome->GetColorMultiplier(y, false);
                        }
                    }
                    break;
                    //Something like black when signal strength is 0 and red when it's 15
                case TintType::Redstone:
#if PROTOCOL_VERSION == 340 // 1.12.2
                    texture_modifier[i] = 0xFF000000 | (25 + 15 * blockstate->GetMetadata());
#elif PROTOCOL_VERSION == 393 // 1.13
                    texture_modifier[i] = 0xFF000000 | (25 + 15 * (((blockstate->GetId() - 1752) / 9) % 16));
#elif PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.1 && 1.13.2
                    texture_modifier[i] = 0xFF000000 | (25 + 15 * (((blockstate->GetId() - 1753) / 9) % 16));
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
					texture_modifier[i] = 0xFF000000 | (25 + 15 * (((blockstate->GetId() - 2056) / 9) % 16));
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
					texture_modifier[i] = 0xFF000000 | (25 + 15 * (((blockstate->GetId() - 2056) / 9) % 16));
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
                    texture_modifier[i] = 0xFF000000 | (25 + 15 * (((blockstate->GetId() - 2058) / 9) % 16));
#else
                    #error "Protocol version not implemented"
#endif
                    break;
                case TintType::Water:
                    if (biome)
                    {
                        texture_modifier[i] = biome->GetWaterColorMultiplier();
                    }
                    break;
                default:
                    break;
                }
            }
            return texture_modifier;
        }
        
        void CubeWorldRenderer::SetDayTime(const float day_time_)
        {
            day_time = day_time_;
        }

        void CubeWorldRenderer::UpdateBuffer()
        {
            faces_should_be_updated = true;
        }

        void CubeWorldRenderer::SetPosOrientation(const double x_, const double y_, const double z_, const float yaw_, const float pitch_)
        {
            if (camera)
            {
                m_mutex_camera.lock();
                camera->SetPosition((float)x_, (float)y_, (float)z_);
                camera->SetRotation(pitch_, yaw_);
                m_mutex_camera.unlock();
            }
        }

        void CubeWorldRenderer::SetMouseCallback(std::function<void(double, double)> callback)
        {
            MouseCallback = callback;
        }

        void CubeWorldRenderer::SetKeyboardCallback(std::function<void(std::array<bool, (int)KEY_CODE::NUMBER_OF_KEYS>, double)> callback)
        {
            KeyboardCallback = callback;
        }

        void CubeWorldRenderer::Screenshot(const std::string &path)
        {
            screenshot_path = path;
            take_screenshot = true;
        }

        bool CubeWorldRenderer::Init()
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

            if (headless)
            {
                glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
            }

            window = glfwCreateWindow(current_window_width, current_window_height, "CubeWorldRenderer", NULL, NULL);
            if (window == NULL)
            {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return false;
            }
            glfwMakeContextCurrent(window);
            //set the user pointer of the window to this object to pass it to the callbacks
            glfwSetWindowUserPointer(window, this);
            glfwSetFramebufferSizeCallback(window, &CubeWorldRenderer::ResizeCallback);
            glfwSetCursorPosCallback(window, &CubeWorldRenderer::InternalMouseCallback);

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            // glad: load all OpenGL function pointers
            // ---------------------------------------
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return false;
            }

#ifdef USE_IMGUI
            // imgui: setup context
            // ---------------------------------------
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();

            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

            // Style
            ImGui::StyleColorsDark();

            // Setup platform/renderer
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");
#endif

            my_shader = std::unique_ptr<Shader>(new Shader);

            glEnable(GL_DEPTH_TEST);
            //glEnable(GL_CULL_FACE); 
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //Set an uniform buffer for view matrix
            unsigned int uniform_view_block_index = glGetUniformBlockIndex(my_shader->Program(), "MatriceView");
            glUniformBlockBinding(my_shader->Program(), uniform_view_block_index, 0);

            glGenBuffers(1, &view_uniform_buffer);
            glBindBuffer(GL_UNIFORM_BUFFER, view_uniform_buffer);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            glBindBufferRange(GL_UNIFORM_BUFFER, 0, view_uniform_buffer, 0, sizeof(glm::mat4));

            //Create a texture
            glGenTextures(1, &atlas_texture);
            glBindTexture(GL_TEXTURE_2D, atlas_texture);

            //Options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas->GetWidth(), atlas->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, atlas->Get());
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);

            return true;
        }

        void CubeWorldRenderer::ResizeCallback(GLFWwindow *window, int width, int height)
        {
            CubeWorldRenderer *this_object = static_cast<CubeWorldRenderer*>(glfwGetWindowUserPointer(window));
            this_object->current_window_width = width;
            this_object->current_window_height = height;
            glViewport(0, 0, width, height);
            this_object->has_proj_changed = true;
        }

        void CubeWorldRenderer::InternalMouseCallback(GLFWwindow *window, double xpos, double ypos)
        {
            CubeWorldRenderer *this_object = static_cast<CubeWorldRenderer*>(glfwGetWindowUserPointer(window));

            if (this_object->first_mouse)
            {
                this_object->mouse_last_x = xpos;
                this_object->mouse_last_y = ypos;
                this_object->first_mouse = false;
            }

            double xoffset = xpos - this_object->mouse_last_x;
            double yoffset = this_object->mouse_last_y - ypos;

            this_object->mouse_last_x = xpos;
            this_object->mouse_last_y = ypos;
            this_object->MouseCallback(xoffset, yoffset);
        }

        void CubeWorldRenderer::InternalProcessInput(GLFWwindow *window)
        {
            std::array<bool, (int)KEY_CODE::NUMBER_OF_KEYS> isKeyPressed;
            for (int i = 0; i < isKeyPressed.size(); ++i)
            {
                isKeyPressed[i] = false;
            }

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                isKeyPressed[(int)KEY_CODE::ESC] = true;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                isKeyPressed[(int)KEY_CODE::SPACE] = true;
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                isKeyPressed[(int)KEY_CODE::SHIFT] = true;
            }
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                isKeyPressed[(int)KEY_CODE::FORWARD] = true;
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                isKeyPressed[(int)KEY_CODE::BACKWARD] = true;
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                isKeyPressed[(int)KEY_CODE::LEFT] = true;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                isKeyPressed[(int)KEY_CODE::RIGHT] = true;
            }
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                isKeyPressed[(int)KEY_CODE::MOUSE_LEFT] = true;
            }

#ifdef USE_IMGUI
            if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
            {
                imgui_demo = !imgui_demo;
            }
#endif

            if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
            {
                screenshot_path = "screenshot.png";
                take_screenshot = true;
            }

            KeyboardCallback(isKeyPressed, deltaTime);
        }

        float CubeWorldRenderer::DistanceToCamera(const Position& chunk)
        {
            return camera->GetDistance(CHUNK_WIDTH * (chunk.x + 0.5f), section_height * (chunk.y + 0.5f), CHUNK_WIDTH * (chunk.z + 0.5f));
        }

        void CubeWorldRenderer::RenderFaces()
        {
            const std::array<glm::vec4, 6> &frustum_planes = camera->GetFrustumPlanes();

            // Get a list of all loaded chunks
            std::unordered_set<Position> all_loaded_chunks;
            all_loaded_chunks.reserve(chunks.size() + transparent_chunks.size());
            int num_faces = 0;

            chunks_mutex.lock();
            for (auto it = chunks.begin(); it != chunks.end(); ++it)
            {
                all_loaded_chunks.insert(it->first);
                num_faces += it->second->GetNumFace();
            }
            chunks_mutex.unlock();
            transparent_chunks_mutex.lock();
            for (auto it = transparent_chunks.begin(); it != transparent_chunks.end(); ++it)
            {
                all_loaded_chunks.insert(it->first);
                num_faces += it->second->GetNumFace();
            }
            transparent_chunks_mutex.unlock();
            const int num_chunks = all_loaded_chunks.size();

            // Apply frustum culling to render only the visible ones
            std::vector<Position> chunks_to_render;
            chunks_to_render.reserve(all_loaded_chunks.size());
            // Frustum culling algorithm from http://old.cescg.org/CESCG-2002/DSykoraJJelinek/
            for (auto it = all_loaded_chunks.begin(); it != all_loaded_chunks.end(); ++it)
            {
                FrustumResult result = FrustumResult::Inside;

                const float min_x = CHUNK_WIDTH * (*it).x;
                const float max_x = CHUNK_WIDTH * ((*it).x + 1);
                const float min_y = (int)section_height * (*it).y;
                const float max_y = (int)section_height * ((*it).y + 1);
                const float min_z = CHUNK_WIDTH * (*it).z;
                const float max_z = CHUNK_WIDTH * ((*it).z + 1);

                for (int i = 0; i < 6; ++i)
                {
                    const bool sign_x = frustum_planes[i].x > 0.0f;
                    const bool sign_y = frustum_planes[i].y > 0.0f;
                    const bool sign_z = frustum_planes[i].z > 0.0f;

                    const glm::vec4 p_vertex = glm::vec4(sign_x ? max_x : min_x, sign_y ? max_y : min_y, sign_z ? max_z : min_z, 1.0f);

                    if (glm::dot(frustum_planes[i], p_vertex) < 0.0f)
                    {
                        result = FrustumResult::Outside;
                        break;
                    }

                    const glm::vec4 n_vertex = glm::vec4(sign_x ? min_x : max_x, sign_y ? min_y : max_y, sign_z ? min_z : max_z, 1.0f);

                    if (glm::dot(frustum_planes[i], n_vertex) < 0.0f)
                    {
                        result = FrustumResult::Intersect;
                    }
                }

                if (result != FrustumResult::Outside)
                {
                    chunks_to_render.push_back(*it);
                }
            }

            // Sort the chunks from far to near the camera
            m_mutex_camera.lock();
            std::sort(chunks_to_render.begin(), chunks_to_render.end(), [this](const Position &p1, const Position&p2){return this->DistanceToCamera(p1) > this->DistanceToCamera(p2); });
            m_mutex_camera.unlock();

            // Render all non partially transparent faces
            const int num_rendered_chunks = chunks_to_render.size();
            int num_rendered_faces = 0;
            chunks_mutex.lock();
            for (int i = 0; i < num_rendered_chunks; ++i)
            {
                auto found_it = chunks.find(chunks_to_render[i]);
                if (found_it != chunks.end())
                {
                    found_it->second->Render();
                    num_rendered_faces += found_it->second->GetNumFace();
                }
            }
            chunks_mutex.unlock();

            m_mutex_camera.lock();
            const glm::vec3 cam_pos = camera->GetPosition();
            m_mutex_camera.unlock();

            // Render all partially transparent faces
            transparent_chunks_mutex.lock();
            for (int i = 0; i < num_rendered_chunks; ++i)
            {
                auto found_it = transparent_chunks.find(chunks_to_render[i]);
                if (found_it != transparent_chunks.end())
                {
                    found_it->second->Sort(cam_pos);
                    found_it->second->Render();
                    num_rendered_faces += found_it->second->GetNumFace();
                }
            }
            transparent_chunks_mutex.unlock();

#ifdef USE_IMGUI
            {
                ImGui::SetNextWindowPos(ImVec2(current_window_width, 0), 0, ImVec2(1.0f, 0.0f));
                ImGui::SetNextWindowSize(ImVec2(175, 125));
                ImGui::Begin("Rendering");
                ImGui::Text("FPS: %.1f (%.2fms)", 1.0 / deltaTime, deltaTime * 1000.0);
                ImGui::Text("Loaded sections: %i", num_chunks);
                ImGui::Text("Rendered sections: %i", num_rendered_chunks);
                ImGui::Text("Loaded faces: %i", num_faces);
                ImGui::Text("Rendered faces: %i", num_rendered_faces);
                ImGui::End();
            }
#endif
        }
    } // Renderer
} // Botcraft