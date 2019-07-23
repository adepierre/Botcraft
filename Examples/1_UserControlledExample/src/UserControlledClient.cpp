#include <botcraft/Game/AssetsManager.hpp>
#include <botcraft/Version.hpp>
#include <botcraft/Game/World.hpp>

#include "UserControlledClient.hpp"

using namespace Botcraft;

UserControlledClient::UserControlledClient(bool online,
    const std::vector<int> &printed_packets_) : InterfaceClient(printed_packets_)
{
#if USE_GUI
    mouse_sensitivity = 0.1f;
#endif

    if (!online)
    {
        world = std::shared_ptr<World>(new World);
        player = std::shared_ptr<Player>(new Player);

        state = State::Play;

        should_be_closed = false;

#ifdef USE_GUI
        renderer = std::shared_ptr<Renderer::CubeWorldRenderer>(new Renderer::CubeWorldRenderer(800, 600, AssetsManager::getInstance().GetTexturesPathsNames(), CHUNK_WIDTH, false));
        mouse_sensitivity = 0.1f;

        // Launch the renderer updater thread
        m_thread_update_renderer = std::thread(&UserControlledClient::WaitForRenderingUpdate, this);

        renderer->SetMouseCallback(std::bind(&UserControlledClient::MouseCallback, this, std::placeholders::_1, std::placeholders::_2));
        renderer->SetKeyboardCallback(std::bind(&UserControlledClient::KeyBoardCallback, this, std::placeholders::_1, std::placeholders::_2));
#endif

        // Launch the thread for the position
        player->SetPosition(Vector3<double>(0.0, 0.0, 0.0));
        m_thread_physics = std::thread(&UserControlledClient::RunSyncPos, this);
        std::cout << "Client created!" << std::endl;

        std::cout << "Creating world..." << std::endl;
        CreateTestWorld();
        std::cout << "Done!" << std::endl;
    }
}

UserControlledClient::~UserControlledClient()
{
    
}

void UserControlledClient::CreateTestWorld()
{
    int max_id = 0;
    int min_id = std::numeric_limits<int>::max();
    for (auto it = AssetsManager::getInstance().Blockstates().begin(); it != AssetsManager::getInstance().Blockstates().end(); ++it)
    {
        if (it->first > max_id)
        {
            max_id = it->first;
        }
        if (it->first < min_id)
        {
            min_id = it->first;
        }
    }

#if PROTOCOL_VERSION < 347
    for (int i = 0; i < (max_id - min_id) / 16 + 1; ++i)
#else
    for (int i = 0; i < (max_id - min_id) / 16 / 16 + 1; ++i)
#endif
    {
        world->AddChunk(i, 0, Dimension::Overworld);
        world->AddChunk(i, 1, Dimension::Overworld);
        world->AddChunk(i, -1, Dimension::Overworld);
        world->AddChunk(i, -2, Dimension::Overworld);
#ifdef USE_GUI
        {
            std::lock_guard<std::mutex> lock_rendering(mutex_rendering);
            positions_to_render.push_back({ Position(i, -1, 0), Position(i, -1, 1), Position(i, -1, -1), Position(i, -1, -2) });
            condition_rendering.notify_all();
        }
#endif
    }

    int x = 0;
#ifdef USE_GUI
    std::vector<Position> updated_positions;
#endif

#if PROTOCOL_VERSION < 347
    for (auto it = AssetsManager::getInstance().Blockstates().begin(); it != AssetsManager::getInstance().Blockstates().end(); ++it)
    {
        int id = it->first;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            const int z = it2->first;

            Position pos;
            if (x % 2 == 0)
            {
                pos = Position(x, 0, 2 * z);
            }
            else
            {
                pos = Position(x, 0, -2 * z - 1);
            }

            world->SetBlock(pos, id, z);
            world->SetBiome(pos.x, pos.z, 0);
#ifdef USE_GUI
            updated_positions.push_back(pos);
#endif
        }
        x++;
    }
#else
    int z = 0;
    for (auto it = AssetsManager::getInstance().Blockstates().begin(); it != AssetsManager::getInstance().Blockstates().end(); ++it)
    {
        int id = it->first;

        Position pos;
        if (x % 4 == 0)
        {
            pos = Position(x, 0, 2 * z + 1);
        }
        else if (x % 4 == 1)
        {
            pos = Position(x + 1, 0, 30 - 2 * z + 1);
        }
        else if (x % 4 == 2)
        {
            pos = Position(x, 0, -2 * z - 1);
        }
        else
        {
            pos = Position(x + 1, 0, -30 + 2 * z - 1);
        }

        world->SetBlock(pos, id);
        world->SetBiome(pos.x, pos.z, 0);
#ifdef USE_GUI
        updated_positions.push_back(pos);
#endif
        z++;
        if (z == 16)
        {
            z = 0;
            x++;
        }
    }
#endif

#ifdef USE_GUI
    {
        std::lock_guard<std::mutex> lock_rendering(mutex_rendering);
        positions_to_render.push_back(updated_positions);
        condition_rendering.notify_all();
    }
    updated_positions.clear();
#endif

    int num_biomes = 0;
    for (int i = 0; i < 256; ++i)
    {
        std::shared_ptr<Biome> biome = AssetsManager::getInstance().GetBiome(i);
        if (biome)
        {
            num_biomes++;
        }
    }

    for (int i = 0; i < num_biomes / 16 + 1; ++i)
    {
        world->AddChunk(-i - 1, 0, Dimension::Overworld);
#ifdef USE_GUI
        {
            std::lock_guard<std::mutex> lock_rendering(mutex_rendering);
            positions_to_render.push_back({ Position(-i - 1, -1, 0) });
            condition_rendering.notify_all();
        }
#endif
    }

    x = 0;
#ifdef USE_GUI
    updated_positions.clear();
#endif
    for (int i = 0; i < 256; ++i)
    {
        std::shared_ptr<Biome> biome = AssetsManager::getInstance().GetBiome(i);
        if (biome)
        {
            Position pos(-x - 1, 0, 0);

#if PROTOCOL_VERSION < 347
            world->SetBlock(pos, 2, 0);
#else
            world->SetBlock(pos, 9);
#endif
            world->SetBiome(pos.x, pos.z, i);
#ifdef USE_GUI
            updated_positions.push_back(pos);
#endif
            pos = Position(-x - 1, 0, 1);

            const Block *block = world->GetBlock(pos);
            std::shared_ptr<Blockstate> previous_blockstate;
            unsigned char previous_model_id;
            if (block != nullptr)
            {
                previous_blockstate = block->GetBlockstate();
                previous_model_id = block->GetModelId();
            }
            else
            {
#if PROTOCOL_VERSION < 347
                previous_blockstate = AssetsManager::getInstance().Blockstates().at(0).at(0);
#else
                previous_blockstate = AssetsManager::getInstance().Blockstates().at(0);
#endif
                previous_model_id = 0;
            }
#if PROTOCOL_VERSION < 347
            world->SetBlock(pos, 18, 0);
#else
            world->SetBlock(pos, 157);
#endif
            world->SetBiome(pos.x, pos.z, i);
#ifdef USE_GUI
            updated_positions.push_back(pos);
#endif
            pos = Position(-x - 1, 0, 2);

            block = world->GetBlock(pos);
            if (block != nullptr)
            {
                previous_blockstate = block->GetBlockstate();
                previous_model_id = block->GetModelId();
            }
            else
            {
#if PROTOCOL_VERSION < 347
                previous_blockstate = AssetsManager::getInstance().Blockstates().at(0).at(0);
#else
                previous_blockstate = AssetsManager::getInstance().Blockstates().at(0);
#endif
                previous_model_id = 0;
            }

#if PROTOCOL_VERSION < 347
            world->SetBlock(pos, 9, 0);
#else
            world->SetBlock(pos, 34);
#endif
            world->SetBiome(pos.x, pos.z, i);
#ifdef USE_GUI
            updated_positions.push_back(pos);
#endif
            x++;
        }
    }
#ifdef USE_GUI
    {
        std::lock_guard<std::mutex> lock_rendering(mutex_rendering);
        positions_to_render.push_back(updated_positions);
        condition_rendering.notify_all();
    }
#endif
    
    player->SetPosition(Vector3<double>(0.5, 1.0, 0.5));
}

#ifdef USE_GUI
void UserControlledClient::MouseCallback(const double &xoffset, const double &yoffset)
{
    float pitch = player->GetPitch() - yoffset * mouse_sensitivity;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
    player->SetPitch(pitch);
    player->SetYaw(player->GetYaw() + xoffset * mouse_sensitivity);

    renderer->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
}

void UserControlledClient::KeyBoardCallback(const std::array<bool, (int)Renderer::KEY_CODE::NUMBER_OF_KEYS> &is_key_pressed, const double &delta_time)
{
    bool pos_has_changed = false;
    if (is_key_pressed[(int)Renderer::KEY_CODE::ESC])
    {
        should_be_closed = true;
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::SPACE])
    {
        if (player->GetOnGround())
        {
            player->SetSpeedY(0.4196141); // Not sure about this. I tried to calculate it in order to get a 1.25 block height jump (reached in 6 ticks)
        }
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::MOUSE_LEFT] && GetDiggingState() == DiggingState::Waiting)
    {
        std::thread thread_digging(&InterfaceClient::Dig, this);
        thread_digging.detach();
    }
    else if (!is_key_pressed[(int)Renderer::KEY_CODE::MOUSE_LEFT] && GetDiggingState() == DiggingState::Digging)
    {
        StopDigging();
    }

    player->SetIsRunning(is_key_pressed[(int)Renderer::KEY_CODE::SHIFT]);

    if (is_key_pressed[(int)Renderer::KEY_CODE::FORWARD])
    {
        player->SetSpeedX(player->GetSpeed().x + player->GetXZVector().x * (player->GetIsRunning() ? 5.612 : 4.317) * delta_time);//TODO replace hardcoded values?
        player->SetSpeedZ(player->GetSpeed().z + player->GetXZVector().z * (player->GetIsRunning() ? 5.612 : 4.317) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::BACKWARD])
    {
        player->SetSpeedX(player->GetSpeed().x - player->GetXZVector().x * (player->GetIsRunning() ? 5.612 : 4.317) * delta_time);//TODO replace hardcoded values?
        player->SetSpeedZ(player->GetSpeed().z - player->GetXZVector().z * (player->GetIsRunning() ? 5.612 : 4.317) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::RIGHT])
    {
        player->SetSpeedX(player->GetSpeed().x + player->GetRightVector().x * (player->GetIsRunning() ? 5.612 : 4.317) * delta_time);//TODO replace hardcoded values?
        player->SetSpeedZ(player->GetSpeed().z + player->GetRightVector().z * (player->GetIsRunning() ? 5.612 : 4.317) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::LEFT])
    {
        player->SetSpeedX(player->GetSpeed().x - player->GetRightVector().x * (player->GetIsRunning() ? 5.612 : 4.317) * delta_time);//TODO replace hardcoded values?
        player->SetSpeedZ(player->GetSpeed().z - player->GetRightVector().z * (player->GetIsRunning() ? 5.612 : 4.317) * delta_time);

        pos_has_changed = true;
    }

    if (pos_has_changed)
    {
        renderer->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62, player->GetPosition().z, player->GetYaw(), player->GetPitch());
    }
}
#endif

void UserControlledClient::Handle(Botcraft::LoginSuccess &msg)
{
    Botcraft::BaseClient::Handle(msg);

#if USE_GUI
    renderer->SetMouseCallback(std::bind(&UserControlledClient::MouseCallback, this, std::placeholders::_1, std::placeholders::_2));
    renderer->SetKeyboardCallback(std::bind(&UserControlledClient::KeyBoardCallback, this, std::placeholders::_1, std::placeholders::_2));
#endif
}