#include "botcraft/Renderer/RenderingManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_set>

#ifdef USE_IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif


#include "botcraft/Renderer/Atlas.hpp"
#include "botcraft/Renderer/BehaviourRenderer.hpp"
#include "botcraft/Renderer/Camera.hpp"
#include "botcraft/Renderer/Chunk.hpp"
#include "botcraft/Renderer/ImageSaver.hpp"
#include "botcraft/Renderer/Shader.hpp"
#include "botcraft/Renderer/TransparentChunk.hpp"
#include "botcraft/Renderer/WorldRenderer.hpp"

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/World/Chunk.hpp"

#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/entities/Entity.hpp"

#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"

#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"

const std::vector<float> color_day({ 0.6f, 0.85f, 0.9f });
const std::vector<float> color_night({0.1f, 0.1f, 0.1f});

namespace Botcraft
{
    namespace Renderer
    {
        RenderingManager::RenderingManager(std::shared_ptr<World> world_, std::shared_ptr<InventoryManager> inventory_manager_,
            std::shared_ptr<EntityManager> entity_manager_,
            const unsigned int &window_width, const unsigned int &window_height,
            const unsigned int section_height_, const bool headless)
        {
            world = world_;
            inventory_manager = inventory_manager_;
            entity_manager = entity_manager_;

            for (int i = 0; i < is_key_pressed.size(); ++i)
            {
                is_key_pressed[i] = false;
            }

            inventory_open = false;
            behaviour_open = false;
            behaviour_renderer = std::make_unique<BehaviourRenderer>();

            mouse_last_x = window_width / 2.0f;
            mouse_last_y = window_height / 2.0f;
            first_mouse = true;

            deltaTime = 0.0f;
            lastFrameTime = 0.0f;

            current_window_width = window_width;
            current_window_height = window_height;
            has_proj_changed = true;

            MouseCallback = [](double, double) {};
            KeyboardCallback = [](std::array<bool, static_cast<int>(KEY_CODE::NUMBER_OF_KEYS)>, double) {};

            world_renderer = std::make_unique<WorldRenderer>(section_height_);

            take_screenshot = false;

            day_time = 0.0f;

            running = true;
            rendering_thread = std::thread(&RenderingManager::Run, this, headless);
            thread_updating_renderable = std::thread(&RenderingManager::WaitForRenderingUpdate, this);
        }

        RenderingManager::~RenderingManager()
        {
            MouseCallback = [](double, double) {};
            KeyboardCallback = [](std::array<bool, static_cast<int>(KEY_CODE::NUMBER_OF_KEYS)>, double) {};

            running = false;

            condition_update.notify_all();
            if (thread_updating_renderable.joinable())
            {
                thread_updating_renderable.join();
            }

            if (rendering_thread.joinable())
            {
                rendering_thread.join();
            }
        }

        void RenderingManager::Run(const bool headless)
        {
            Logger::GetInstance().RegisterThread("RenderingLoop");
            if (!Init(headless))
            {
                LOG_ERROR("Can't init rendering manager");
                return;
            }

            my_shader->Use();
            float real_fps = 1.0f;

            while (!glfwWindowShouldClose(window))
            {
                double currentFrame = glfwGetTime();
                auto start = std::chrono::steady_clock::now();

                //Max 60 FPS
                auto end = start + std::chrono::microseconds(1000000 / 60);

                deltaTime = currentFrame - lastFrameTime;
                lastFrameTime = currentFrame;

                InternalProcessInput(window);

#ifdef USE_IMGUI
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                {
                    ImGui::SetNextWindowPos(ImVec2(0, 0));
                    ImGui::SetNextWindowSize(ImVec2(290, 70));
                    ImGui::Begin("Position", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
                    ImGui::Text("%f, %f, %f", world_renderer->GetCamera()->GetPosition().x, world_renderer->GetCamera()->GetPosition().y - 1.62f, world_renderer->GetCamera()->GetPosition().z);
                    ImGui::Text("Yaw: %f  ||  ", world_renderer->GetCamera()->GetYaw());
                    ImGui::SameLine();
                    ImGui::Text("Pitch: %f", world_renderer->GetCamera()->GetPitch());
                    ImGui::End();
                }
                {
                    ImGui::SetNextWindowPos(ImVec2(0, 75));
                    ImGui::SetNextWindowSize(ImVec2(290, 70));
                    ImGui::Begin("Targeted cube", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
                    Position raycasted_pos;
                    Position raycasted_normal;
                    const Blockstate* raycasted_blockstate;
                    {
                        std::lock_guard<std::mutex> world_guard(world->GetMutex());
                        raycasted_blockstate =
                            world->Raycast(Vector3<double>(world_renderer->GetCamera()->GetPosition().x, world_renderer->GetCamera()->GetPosition().y, world_renderer->GetCamera()->GetPosition().z),
                            Vector3<double>(world_renderer->GetCamera()->GetFront().x, world_renderer->GetCamera()->GetFront().y, world_renderer->GetCamera()->GetFront().z),
                            6.0f, raycasted_pos, raycasted_normal);
                    }
                    if (raycasted_blockstate)
                    {
                        ImGui::Text("Watching block at %i, %i, %i", raycasted_pos.x, raycasted_pos.y, raycasted_pos.z);
                        ImGui::Text("Block: %s", raycasted_blockstate->GetName().c_str());
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
                world_renderer->UpdateViewMatrix();

                if (has_proj_changed)
                {
                    glm::mat4 projection = glm::perspective(glm::radians(45.0f), current_window_width / static_cast<float>(current_window_height), 0.1f, 200.0f);
                    my_shader->SetMat4("projection", projection);
                    world_renderer->SetCameraProjection(projection);
                    has_proj_changed = false;
                }
                
                world_renderer->UpdateFaces();

                my_shader->Use();

                //Draw all faces
                world_renderer->UseAtlasTextureGL();

#ifdef USE_IMGUI
                int num_chunks, num_rendered_chunks, num_entities, num_rendered_entities, num_faces, num_rendered_faces;
                world_renderer->RenderFaces(&num_chunks, &num_rendered_chunks, &num_entities, &num_rendered_entities, &num_faces, &num_rendered_faces);
                {
                    ImGui::SetNextWindowPos(ImVec2(static_cast<float>(current_window_width), 0.0f), 0, ImVec2(1.0f, 0.0f));
                    ImGui::SetNextWindowSize(ImVec2(180.0f, 170.0f));
                    ImGui::Begin("Rendering", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
                    ImGui::Text("Lim. FPS: %.1f (%.2fms)", 1.0 / deltaTime, deltaTime * 1000.0);
                    ImGui::Text("Real FPS: %.1f (%.2fms)", 1.0 / real_fps, real_fps * 1000.0);
                    ImGui::Text("Loaded sections: %i", num_chunks);
                    ImGui::Text("Rendered sections: %i", num_rendered_chunks);
                    ImGui::Text("Num entities: %i", num_entities);
                    ImGui::Text("Rendered entities: %i", num_rendered_entities);
                    ImGui::Text("Loaded faces: %i", num_faces);
                    ImGui::Text("Rendered faces: %i", num_rendered_faces);
                    ImGui::End();
                }
#else
                world_renderer->RenderFaces();
#endif

                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);

#ifdef USE_IMGUI
                // Draw the behaviour if it's open
                if (behaviour_open)
                {
                    const int blackboard_width = static_cast<int>((static_cast<float>(current_window_width) - 30.0f) / 5.0f);

                    ImGui::SetNextWindowPos(ImVec2(15.0f, 15.0f), 0, ImVec2(0.0f, 0.0f));
                    ImGui::SetNextWindowSize(ImVec2(blackboard_width, current_window_height - 30.0f));
                    ImGui::Begin("Blackboard", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse);
                    behaviour_renderer->RenderBlackboard();
                    ImGui::End();

                    ImGui::SetNextWindowPos(ImVec2(15.0f + blackboard_width, 15.0f), 0, ImVec2(0.0f, 0.0f));
                    ImGui::SetNextWindowSize(ImVec2(current_window_width - blackboard_width - 30.0f, current_window_height - 30.0f));
                    ImGui::Begin("Behaviour", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
                    behaviour_renderer->RenderNodes();
                    ImGui::End();
                }

                // Draw the inventory if it's open
                if (inventory_open)
                {
                    ImGui::SetNextWindowPos(ImVec2(static_cast<float>(current_window_width), static_cast<float>(current_window_height)), 0, ImVec2(1.0f, 1.0f));
                    ImGui::SetNextWindowSize(ImVec2(300.0f, current_window_height - 175.0f));
                    ImGui::Begin("Inventory", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
                    if (inventory_manager && inventory_manager->GetPlayerInventory())
                    {
                        const std::map<short, ProtocolCraft::Slot>& slots = inventory_manager->GetPlayerInventory()->GetSlots();
                        for (short i = 0; i <= Window::INVENTORY_OFFHAND_INDEX; ++i)
                        {
                            auto it = slots.find(i);
                            if (it == slots.end())
                            {
                                continue;
                            }
                            if (i == Window::INVENTORY_CRAFTING_OUTPUT_INDEX)
                            {
                                ImGui::Text("Crafting output");
                            }
                            else if (i == Window::INVENTORY_CRAFTING_INPUT_START)
                            {
                                ImGui::Text("Crafting input");
                            }
                            else if (i == Window::INVENTORY_ARMOR_START)
                            {
                                ImGui::Text("Equiped Armor");
                            }
                            else if (i == Window::INVENTORY_STORAGE_START)
                            {
                                ImGui::Text("Inventory");
                            }
                            else if (i == Window::INVENTORY_HOTBAR_START)
                            {
                                ImGui::Text("Hotbar");
                            }
                            else if (i == Window::INVENTORY_OFFHAND_INDEX)
                            {
                                ImGui::Text("Offhand");
                            }
#if PROTOCOL_VERSION < 347
                            std::string name = AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(static_cast<unsigned char>(it->second.GetItemDamage()))->GetName();
#else
                            std::string name = AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName();
#endif
                            if (name != "minecraft:air")
                            {
                                ImGui::Text(std::string("    (%i) " + name + " (x%i)").c_str(), i, it->second.GetItemCount());
                            }
                        }
                    }
                    ImGui::End();
                }


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

                real_fps = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() / 1e6);
                
                //Wait to have 60 FPS
                SleepUntil(end);
            }

            world_renderer.reset();
            my_shader.reset();

#ifdef USE_IMGUI
            behaviour_renderer->CleanUp();
            // ImGui cleaning
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
#endif

            glfwDestroyWindow(window);
            glfwTerminate();
        }

        void RenderingManager::Close()
        {
            glfwSetWindowShouldClose(window, true);
            running = false;
        }

        void RenderingManager::SetMouseCallback(std::function<void(double, double)> callback)
        {
            MouseCallback = callback;
        }

        void RenderingManager::SetKeyboardCallback(std::function<void(std::array<bool, static_cast<int>(KEY_CODE::NUMBER_OF_KEYS)>, double)> callback)
        {
            KeyboardCallback = callback;
        }

        void RenderingManager::Screenshot(const std::string &path)
        {
            screenshot_path = path;
            take_screenshot = true;
        }

        void RenderingManager::SetCurrentBehaviourTree(const BaseNode* root) const
        {
            behaviour_renderer->SetCurrentBehaviourTree(root);
        }

        void RenderingManager::ResetBehaviourState() const
        {
            behaviour_renderer->ResetBehaviourState();
        }

        void RenderingManager::BehaviourStartTick() const
        {
            behaviour_renderer->BehaviourStartTick();
        }

        void RenderingManager::BehaviourEndTick(const bool b) const
        {
            behaviour_renderer->BehaviourEndTick(b);
        }

        void RenderingManager::BehaviourTickChild(const size_t i) const
        {
            behaviour_renderer->BehaviourTickChild(i);
        }

        bool RenderingManager::IsBehaviourGUIPaused() const
        {
            return behaviour_renderer->IsBehaviourPaused();
        }

        void RenderingManager::ResetBlackboard() const
        {
            behaviour_renderer->ResetBlackboard();
        }

        void RenderingManager::UpdateBlackboardValue(const std::string& key, const std::any& value) const
        {
            behaviour_renderer->UpdateBlackboardValue(key, value);
        }

        void RenderingManager::RemoveBlackboardValue(const std::string& key) const
        {
            behaviour_renderer->RemoveBlackboardValue(key);
        }

        bool RenderingManager::Init(const bool headless)
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

            window = glfwCreateWindow(current_window_width, current_window_height, "RenderingManager", NULL, NULL);
            if (window == NULL)
            {
                LOG_ERROR("Failed to create GLFW window");
                glfwTerminate();
                return false;
            }
            glfwMakeContextCurrent(window);
            //set the user pointer of the window to this object to pass it to the callbacks
            glfwSetWindowUserPointer(window, this);
            glfwSetFramebufferSizeCallback(window, &RenderingManager::ResizeCallback);
            glfwSetCursorPosCallback(window, &RenderingManager::InternalMouseCallback);

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            // glad: load all OpenGL function pointers
            // ---------------------------------------
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                LOG_ERROR("Failed to initialize GLAD");
                return false;
            }

#ifdef USE_IMGUI
            // imgui: setup context
            // ---------------------------------------
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            behaviour_renderer->Init();

            ImGuiIO &io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

            // Style
            ImGui::StyleColorsDark();

            // Setup platform/renderer
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");
#endif

            my_shader = std::make_unique<Shader>();

            glEnable(GL_DEPTH_TEST);
            //glEnable(GL_CULL_FACE); 
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //Set an uniform buffer for view matrix
            unsigned int uniform_view_block_index = glGetUniformBlockIndex(my_shader->Program(), "MatriceView");
            glUniformBlockBinding(my_shader->Program(), uniform_view_block_index, 0);

            world_renderer->InitGL();

            return true;
        }

        void RenderingManager::ResizeCallback(GLFWwindow *window, int width, int height)
        {
            RenderingManager *this_object = static_cast<RenderingManager*>(glfwGetWindowUserPointer(window));
            this_object->current_window_width = width;
            this_object->current_window_height = height;
            glViewport(0, 0, width, height);
            this_object->has_proj_changed = true;
        }

        void RenderingManager::InternalMouseCallback(GLFWwindow *window, double xpos, double ypos)
        {
            RenderingManager *this_object = static_cast<RenderingManager*>(glfwGetWindowUserPointer(window));

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

            if (this_object->inventory_open || this_object->behaviour_open)
            {
                return;
            }

            this_object->MouseCallback(xoffset, yoffset);
        }

        void RenderingManager::InternalProcessInput(GLFWwindow *window)
        {
            is_key_pressed[static_cast<int>(KEY_CODE::FORWARD)] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
            is_key_pressed[static_cast<int>(KEY_CODE::BACKWARD)] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
            is_key_pressed[static_cast<int>(KEY_CODE::RIGHT)] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
            is_key_pressed[static_cast<int>(KEY_CODE::LEFT)] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
            is_key_pressed[static_cast<int>(KEY_CODE::SPACE)] = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
            is_key_pressed[static_cast<int>(KEY_CODE::SHIFT)] = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
            is_key_pressed[static_cast<int>(KEY_CODE::CTRL)] = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
            is_key_pressed[static_cast<int>(KEY_CODE::ESC)] = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
            is_key_pressed[static_cast<int>(KEY_CODE::MOUSE_LEFT)] = glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
            const bool is_inventory_key_pressed = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;

            // Toggle inventory if E was not pressed during previous frame and is during this one
            const bool toggle_inventory = (!is_key_pressed[static_cast<int>(KEY_CODE::INVENTORY)] && is_inventory_key_pressed);
            // Save current value just like others
            is_key_pressed[static_cast<int>(KEY_CODE::INVENTORY)] = is_inventory_key_pressed;


            const bool is_behaviour_key_pressed = glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS;

            // Toggle behaviour if B was not pressed during previous frame and is during this one
            const bool toggle_behaviour = (!is_key_pressed[static_cast<int>(KEY_CODE::BEHAVIOUR)] && is_behaviour_key_pressed);
            // Save current value just like others
            is_key_pressed[static_cast<int>(KEY_CODE::BEHAVIOUR)] = is_behaviour_key_pressed;

#ifdef USE_IMGUI
            if (toggle_inventory)
            {
                inventory_open = !inventory_open;
            }

            if (toggle_behaviour)
            {
                behaviour_open = !behaviour_open;
            }

            if (inventory_open || behaviour_open)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
#endif

            if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
            {
                screenshot_path = "screenshot.png";
                take_screenshot = true;
            }

            KeyboardCallback(is_key_pressed, deltaTime);
        }

        void RenderingManager::AddChunkToUpdate(const int x, const int z)
        {
            const std::vector<Position> chunk_pos = { {Position(x, 0, z), Position(x - 1, 0, z),
                            Position(x + 1, 0 , z), Position(x, 0, z - 1), Position(x, 0, z + 1)} };

            std::lock_guard<std::mutex> guard_rendering(mutex_updating);
            for (int i = 0; i < chunk_pos.size(); ++i)
            {
                chunks_to_udpate.insert(chunk_pos[i]);
            }
            condition_update.notify_all();
        }

        void RenderingManager::AddEntityToUpdate(const int id)
        {
            std::lock_guard<std::mutex> guard_rendering(mutex_updating);
            entities_to_update.insert(id);
            condition_update.notify_all();
        }

        void RenderingManager::SetPosOrientation(const double x_, const double y_, const double z_, const float yaw_, const float pitch_)
        {
            if (world_renderer)
            {
                world_renderer->SetPosOrientation(x_, y_, z_, yaw_, pitch_);
            }
        }

        void RenderingManager::WaitForRenderingUpdate()
        {
            Logger::GetInstance().RegisterThread("RenderingDataUpdate");
            while (running)
            {
                {
                    std::unique_lock<std::mutex> lck(mutex_updating);
                    condition_update.wait(lck);
                }

                while (!chunks_to_udpate.empty())
                {
                    Position pos;
                    mutex_updating.lock();
                    if (!chunks_to_udpate.empty())
                    {
                        auto posIterator = chunks_to_udpate.begin();
                        pos = *posIterator;
                        chunks_to_udpate.erase(posIterator);
                    }
                    mutex_updating.unlock();

                    std::shared_ptr<const Botcraft::Chunk> chunk;
                    // Get the new values in the world
                    world->GetMutex().lock();
                    bool has_chunk_been_modified = world->HasChunkBeenModified(pos.x, pos.z);
                    if (has_chunk_been_modified)
                    {
                        chunk = world->GetChunkCopy(pos.x, pos.z);
                        world->ResetChunkModificationState(pos.x, pos.z);
                    }
                    world->GetMutex().unlock();

                    if (has_chunk_been_modified)
                    {
                        world_renderer->UpdateChunk(pos.x, pos.z, chunk);
                    }

                    // If we left the game, we don't need to process 
                    // the rest of the data, just discard them
                    if (!running)
                    {
                        mutex_updating.lock();
                        chunks_to_udpate.clear();
                        mutex_updating.unlock();
                        break;
                    }
                }

                while (!entities_to_update.empty())
                {
                    int entity_id = -1;
                    mutex_updating.lock();
                    if (!entities_to_update.empty())
                    {
                        auto eid_it = entities_to_update.begin();
                        entity_id = *eid_it;
                        entities_to_update.erase(eid_it);
                    }
                    mutex_updating.unlock();

                    std::vector<Face> faces;
                    // Get the new values
                    entity_manager->GetMutex().lock();
                    std::shared_ptr<Botcraft::Entity> entity = entity_manager->GetEntity(entity_id);
                    bool should_update = false;
                    if (entity == nullptr)
                    {
                        should_update = true;
                    }
                    else if (!entity->GetAreRenderedFacesUpToDate())
                    {
                        faces = entity->GetFaces();
                        entity->SetAreRenderedFacesUpToDate(true);
                        should_update = true;
                    }
                    entity_manager->GetMutex().unlock();

                    if (should_update)
                    {
                        world_renderer->UpdateEntity(entity_id, faces);
                    }

                    // If we left the game, we don't need to process 
                    // the rest of the data, just discard them
                    if (!running)
                    {
                        mutex_updating.lock();
                        entities_to_update.clear();
                        mutex_updating.unlock();
                        break;
                    }
                }
            }
        }

        /*
        *  Packet handling methods
        */
        void RenderingManager::Handle(ProtocolCraft::Message& msg)
        {

        }

        void RenderingManager::Handle(ProtocolCraft::ClientboundBlockUpdatePacket& msg)
        {
            Position chunk_coords = Botcraft::Chunk::BlockCoordsToChunkCoords(msg.GetPos());
            AddChunkToUpdate(chunk_coords.x, chunk_coords.z);
        }

        void RenderingManager::Handle(ProtocolCraft::ClientboundSectionBlocksUpdatePacket& msg)
        {
#if PROTOCOL_VERSION < 737
            AddChunkToUpdate(msg.GetChunkX(), msg.GetChunkZ());
#else
            AddChunkToUpdate(msg.GetSectionPos() >> 42, msg.GetSectionPos() << 22 >> 42);
#endif
        }

        void RenderingManager::Handle(ProtocolCraft::ClientboundForgetLevelChunkPacket& msg)
        {
            AddChunkToUpdate(msg.GetX(), msg.GetZ());
        }

#if PROTOCOL_VERSION < 757
        void RenderingManager::Handle(ProtocolCraft::ClientboundLevelChunkPacket& msg)
#else
        void RenderingManager::Handle(ProtocolCraft::ClientboundLevelChunkWithLightPacket& msg)
#endif
        {
            AddChunkToUpdate(msg.GetX(), msg.GetZ());
        }

        void RenderingManager::Handle(ProtocolCraft::ClientboundAddEntityPacket& msg)
        {
            AddEntityToUpdate(msg.GetId_());
        }

#if PROTOCOL_VERSION < 759
        void RenderingManager::Handle(ProtocolCraft::ClientboundAddMobPacket& msg)
        {
            AddEntityToUpdate(msg.GetId_());
        }
#endif

#if PROTOCOL_VERSION < 721
        void RenderingManager::Handle(ProtocolCraft::ClientboundAddGlobalEntityPacket& msg)
        {
            AddEntityToUpdate(msg.GetId_());
        }
#endif

        void RenderingManager::Handle(ProtocolCraft::ClientboundAddPlayerPacket& msg)
        {
            AddEntityToUpdate(msg.GetEntityId());
        }

        void RenderingManager::Handle(ProtocolCraft::ClientboundTeleportEntityPacket& msg)
        {
            AddEntityToUpdate(msg.GetId_());
        }

#if PROTOCOL_VERSION < 755
        void RenderingManager::Handle(ProtocolCraft::ClientboundMoveEntityPacket& msg)
        {
            AddEntityToUpdate(msg.GetEntityId());
        }
#endif

        void RenderingManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& msg)
        {
            AddEntityToUpdate(msg.GetEntityId());
        }

        void RenderingManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& msg)
        {
            AddEntityToUpdate(msg.GetEntityId());
        }

        void RenderingManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& msg)
        {
            AddEntityToUpdate(msg.GetEntityId());
        }

#if PROTOCOL_VERSION == 755
        void RenderingManager::Handle(ProtocolCraft::ClientboundRemoveEntityPacket& msg)
        {
            AddEntityToUpdate(msg.GetEntityId());
        }
#else
        void RenderingManager::Handle(ProtocolCraft::ClientboundRemoveEntitiesPacket& msg)
        {
            for (auto id: msg.GetEntityIds())
            {
                AddEntityToUpdate(id);
            }
        }
#endif

        void RenderingManager::Handle(ProtocolCraft::ClientboundSetTimePacket& msg)
        {
            day_time = ((msg.GetDayTime() + 6000) % 24000) / 24000.0f;
        }

        void RenderingManager::Handle(ProtocolCraft::ClientboundRespawnPacket& msg)
        {
            world_renderer->ClearFaces();
        }
    } // Renderer
} // Botcraft
