#include <botcraft/Game/AssetsManager.hpp>
#include <botcraft/Version.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>
#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/World/Chunk.hpp>
#include <botcraft/Network/NetworkManager.hpp>
#include <protocolCraft/enums.hpp>

#if USE_GUI
#include <botcraft/Renderer/RenderingManager.hpp>
#endif

#include "UserControlledClient.hpp"

using namespace Botcraft;
using namespace ProtocolCraft;

UserControlledClient::UserControlledClient(bool online, bool use_renderer_) : InterfaceClient(use_renderer_)
{
#if USE_GUI
    mouse_sensitivity = 0.1f;
#endif

    if (!online)
    {
        network_manager = std::shared_ptr<NetworkManager>(new NetworkManager(ConnectionState::Play));
        world = std::shared_ptr<World>(new World(false));
        entity_manager = std::shared_ptr<EntityManager>(new EntityManager);

        should_be_closed = false;

#ifdef USE_GUI
        if (use_renderer)
        {
            rendering_manager = std::shared_ptr<Renderer::RenderingManager>(new Renderer::RenderingManager(world, inventory_manager, 800, 600, AssetsManager::getInstance().GetTexturesPathsNames(), CHUNK_WIDTH, false));
            mouse_sensitivity = 0.1f;

            rendering_manager->SetMouseCallback(std::bind(&UserControlledClient::MouseCallback, this, std::placeholders::_1, std::placeholders::_2));
            rendering_manager->SetKeyboardCallback(std::bind(&UserControlledClient::KeyBoardCallback, this, std::placeholders::_1, std::placeholders::_2));
        }
#endif

        // Launch the thread for the position
        entity_manager->GetLocalPlayer()->SetPosition(Vector3<double>(0.0, 0.0, 0.0));
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
#if PROTOCOL_VERSION < 719
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif
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
        world->AddChunk(i, 0, dimension);
        world->AddChunk(i, 1, dimension);
        world->AddChunk(i, -1, dimension);
        world->AddChunk(i, -2, dimension);
    }

    int x = 0;

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

        z++;
        if (z == 16)
        {
            z = 0;
            x++;
        }
    }
#endif

#ifdef USE_GUI
    if (use_renderer)
    {
        for (int i = 0; i < (int)floor(x / CHUNK_WIDTH) + 1; ++i)
        {
            rendering_manager->AddChunkToUpdate(i, 0);
            rendering_manager->AddChunkToUpdate(i, 1);
            rendering_manager->AddChunkToUpdate(i, -1);
            rendering_manager->AddChunkToUpdate(i, -2);
        }
    }
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

#if PROTOCOL_VERSION < 552
	const int biome_spacing = 1;
#else
	const int biome_spacing = 4;
#endif

    for (int i = 0; i < (num_biomes * biome_spacing) / 16 + 1; ++i)
    {
        world->AddChunk(-i - 1, 0, dimension);
    }

    x = 0;
    for (int i = 0; i < 256; ++i)
    {
        std::shared_ptr<Biome> biome = AssetsManager::getInstance().GetBiome(i);
        if (biome)
        {
            Position pos(-(x * biome_spacing) - 1, 0, 0);

#if PROTOCOL_VERSION < 347
            world->SetBlock(pos, 2, 0);
#else
            world->SetBlock(pos, 9);
#endif
#if PROTOCOL_VERSION < 552
            world->SetBiome(pos.x, pos.z, i);
#else
			world->SetBiome(pos.x, pos.y, pos.z, i);
#endif
            pos = Position(-(x * biome_spacing) - 1, 0, 1);

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
#if PROTOCOL_VERSION < 552
			world->SetBiome(pos.x, pos.z, i);
#else
			world->SetBiome(pos.x, pos.y, pos.z, i);
#endif
            pos = Position(-(x * biome_spacing) - 1, 0, 2);

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
#if PROTOCOL_VERSION < 552
			world->SetBiome(pos.x, pos.z, i);
#else
			world->SetBiome(pos.x, pos.y, pos.z, i);
#endif
            x++;
        }
    }
#ifdef USE_GUI
    if (use_renderer)
    {
        for (int i = 0; i < (num_biomes * biome_spacing) / 16 + 1; ++i)
        {
            rendering_manager->AddChunkToUpdate(-i - 1, 0);
        }
    }
#endif
    
    entity_manager->GetLocalPlayer()->SetPosition(Vector3<double>(0.5, 1.0, 0.5));
}

#ifdef USE_GUI
void UserControlledClient::MouseCallback(const double &xoffset, const double &yoffset)
{
    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
    float pitch = local_player->GetPitch() - yoffset * mouse_sensitivity;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
    local_player->SetPitch(pitch);
    local_player->SetYaw(local_player->GetYaw() + xoffset * mouse_sensitivity);

    rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62f, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
}

void UserControlledClient::KeyBoardCallback(const std::array<bool, (int)Renderer::KEY_CODE::NUMBER_OF_KEYS> &is_key_pressed, const double &delta_time)
{
    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
    bool pos_has_changed = false;
    if (is_key_pressed[(int)Renderer::KEY_CODE::ESC])
    {
        should_be_closed = true;
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::SPACE])
    {
        if (local_player->GetOnGround())
        {
            local_player->SetSpeedY(0.4196141); // Not sure about this. I tried to calculate it in order to get a 1.25 block height jump (reached in 6 ticks)
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

    local_player->SetIsRunning(is_key_pressed[(int)Renderer::KEY_CODE::SHIFT]);

    if (is_key_pressed[(int)Renderer::KEY_CODE::FORWARD])
    {
        local_player->SetSpeedX(local_player->GetSpeed().x + local_player->GetXZVector().x * (local_player->GetIsRunning() ? 5.612 : 4.317) * delta_time);//TODO replace hardcoded values?
        local_player->SetSpeedZ(local_player->GetSpeed().z + local_player->GetXZVector().z * (local_player->GetIsRunning() ? 5.612 : 4.317) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::BACKWARD])
    {
        local_player->SetSpeedX(local_player->GetSpeed().x - local_player->GetXZVector().x * (local_player->GetIsRunning() ? 5.612 : 4.317) * delta_time);//TODO replace hardcoded values?
        local_player->SetSpeedZ(local_player->GetSpeed().z - local_player->GetXZVector().z * (local_player->GetIsRunning() ? 5.612 : 4.317) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::RIGHT])
    {
        local_player->SetSpeedX(local_player->GetSpeed().x + local_player->GetRightVector().x * (local_player->GetIsRunning() ? 5.612 : 4.317) * delta_time);//TODO replace hardcoded values?
        local_player->SetSpeedZ(local_player->GetSpeed().z + local_player->GetRightVector().z * (local_player->GetIsRunning() ? 5.612 : 4.317) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[(int)Renderer::KEY_CODE::LEFT])
    {
        local_player->SetSpeedX(local_player->GetSpeed().x - local_player->GetRightVector().x * (local_player->GetIsRunning() ? 5.612 : 4.317) * delta_time);//TODO replace hardcoded values?
        local_player->SetSpeedZ(local_player->GetSpeed().z - local_player->GetRightVector().z * (local_player->GetIsRunning() ? 5.612 : 4.317) * delta_time);

        pos_has_changed = true;
    }

    if (pos_has_changed)
    {
        rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
    }
}
#endif

void UserControlledClient::Handle(LoginSuccess &msg)
{
    Botcraft::BaseClient::Handle(msg);

#if USE_GUI
    if (use_renderer)
    {
        rendering_manager->SetMouseCallback(std::bind(&UserControlledClient::MouseCallback, this, std::placeholders::_1, std::placeholders::_2));
        rendering_manager->SetKeyboardCallback(std::bind(&UserControlledClient::KeyBoardCallback, this, std::placeholders::_1, std::placeholders::_2));
    }
#endif
}