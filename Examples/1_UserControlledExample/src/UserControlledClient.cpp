#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Version.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/entities/Entity.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/Physics/PhysicsManager.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include "protocolCraft/enums.hpp"

#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

#include "UserControlledClient.hpp"

#include <iostream>

using namespace Botcraft;
using namespace ProtocolCraft;

UserControlledClient::UserControlledClient(bool online, bool use_renderer_) : ManagersClient(use_renderer_)
{
#if USE_GUI
    mouse_sensitivity = 0.1f;
#endif

    if (!online)
    {
        network_manager = std::make_shared<NetworkManager>(ConnectionState::Play);
        world = std::make_shared<World>(false);
        entity_manager = std::make_shared<EntityManager>();
        inventory_manager = std::make_shared<InventoryManager>();

        should_be_closed = false;

#ifdef USE_GUI
        if (use_renderer)
        {
            rendering_manager = std::make_shared<Renderer::RenderingManager>(world, inventory_manager, entity_manager, 800, 600, CHUNK_WIDTH, false);
            mouse_sensitivity = 0.1f;

            rendering_manager->SetMouseCallback(std::bind(&UserControlledClient::MouseCallback, this, std::placeholders::_1, std::placeholders::_2));
            rendering_manager->SetKeyboardCallback(std::bind(&UserControlledClient::KeyBoardCallback, this, std::placeholders::_1, std::placeholders::_2));
        }
        physics_manager = std::make_shared<PhysicsManager>(rendering_manager, inventory_manager, entity_manager, network_manager, world);
#else
        physics_manager = std::make_shared<PhysicsManager>(inventory_manager, entity_manager, network_manager, world);
#endif

        // Launch the thread for the position
        entity_manager->GetLocalPlayer()->SetPosition(Vector3<double>(0.0, 0.0, 0.0));
        physics_manager->StartPhysics();
        LOG_INFO("Client created!");

        LOG_INFO("Creating world...");
        CreateTestWorld();
        LOG_INFO("Done!");
    }
}

UserControlledClient::~UserControlledClient()
{
    
}

void UserControlledClient::CreateTestWorld()
{
#if PROTOCOL_VERSION < 719 /* < 1.16 */
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    world->SetDimensionMinY(dimension, 0);
    world->SetDimensionHeight(dimension, 256);
    world->SetCurrentDimension(dimension);
#endif

    std::shared_ptr<Entity> entity = Entity::CreateEntity(EntityType::Zombie);
    entity->SetEntityID(42);
    entity->SetPosition(Vector3<double>(0.0, 1.0, 0.0));
    entity->SetYaw(45.0f);
    entity_manager->AddEntity(entity);
#ifdef USE_GUI
    if (use_renderer)
    {
        rendering_manager->AddEntityToUpdate(entity->GetEntityID());
    }
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

#if PROTOCOL_VERSION < 347 /* < 1.13 */
    for (int i = 0; i < (max_id - min_id) / 16 + 1; ++i)
#else
    for (int i = 0; i < (max_id - min_id) / 16 / 16 + 1; ++i)
#endif
    {
        world->LoadChunk(i, 0, dimension);
        world->LoadChunk(i, 1, dimension);
        world->LoadChunk(i, -1, dimension);
        world->LoadChunk(i, -2, dimension);
    }

    int x = 0;

#if PROTOCOL_VERSION < 347 /* < 1.13 */
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

            world->SetBlock(pos, { id, z });
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
        for (int i = 0; i < static_cast<int>(floor(x / CHUNK_WIDTH)) + 1; ++i)
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
        const Biome* biome = AssetsManager::getInstance().GetBiome(i);
        if (biome)
        {
            num_biomes++;
        }
    }

#if PROTOCOL_VERSION < 552 /* < 1.15 */
    const int biome_spacing = 1;
#else
    const int biome_spacing = 4;
#endif

    for (int i = 0; i < (num_biomes * biome_spacing) / 16 + 1; ++i)
    {
        world->LoadChunk(-i - 1, 0, dimension);
    }

    x = 0;
    for (int i = 0; i < 256; ++i)
    {
        const Biome* biome = AssetsManager::getInstance().GetBiome(i);
        if (biome)
        {
            Position pos(-(x * biome_spacing) - 1, 0, 0);

#if PROTOCOL_VERSION < 347 /* < 1.13 */
            world->SetBlock(pos, { 2, 0 });
#else
            world->SetBlock(pos, 9);
#endif
#if PROTOCOL_VERSION < 552 /* < 1.15 */
            world->SetBiome(pos.x, pos.z, i);
#else
            world->SetBiome(pos.x, pos.y, pos.z, i);
#endif
            pos = Position(-(x * biome_spacing) - 1, 0, 1);

#if PROTOCOL_VERSION < 347 /* < 1.13 */
            world->SetBlock(pos, { 18, 0 });
#else
            world->SetBlock(pos, 157);
#endif
#if PROTOCOL_VERSION < 552 /* < 1.15 */
            world->SetBiome(pos.x, pos.z, i);
#else
            world->SetBiome(pos.x, pos.y, pos.z, i);
#endif
            pos = Position(-(x * biome_spacing) - 1, 0, 2);

#if PROTOCOL_VERSION < 347 /* < 1.13 */
            world->SetBlock(pos, { 9, 0 });
#else
            world->SetBlock(pos, 34);
#endif
#if PROTOCOL_VERSION < 552 /* < 1.15 */
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
void UserControlledClient::MouseCallback(const double& xoffset, const double& yoffset)
{
    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
    float pitch = static_cast<float>(local_player->GetPitch() - yoffset * mouse_sensitivity);

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
    local_player->SetPitch(pitch);
    float yaw = static_cast<float>(local_player->GetYaw() + xoffset * mouse_sensitivity);
    while (yaw > 360.0f)
    {
        yaw -= 360.0f;
    }
    while (yaw < 0.0f)
    {
        yaw += 360.0f;
    }
    local_player->SetYaw(yaw);
}

void UserControlledClient::KeyBoardCallback(const std::array<bool, static_cast<int>(Renderer::KEY_CODE::NUMBER_OF_KEYS)>& is_key_pressed, const double& delta_time)
{
    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::ESC)])
    {
        should_be_closed = true;
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::SPACE)])
    {
        local_player->SetInputsJump(true);
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::CTRL)])
    {
        local_player->SetInputsSneak(true);
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::SHIFT)])
    {
        local_player->SetInputsSprint(true);
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::FORWARD)])
    {
        local_player->SetInputsForward(1.0);
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::BACKWARD)])
    {
        local_player->SetInputsForward(-1.0);
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::RIGHT)])
    {
        local_player->SetInputsLeft(-1.0);
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::LEFT)])
    {
        local_player->SetInputsLeft(1.0);
    }
}
#endif

void UserControlledClient::Handle(ClientboundGameProfilePacket& msg)
{
    Botcraft::ManagersClient::Handle(msg);

#if USE_GUI
    if (use_renderer)
    {
        rendering_manager->SetMouseCallback(std::bind(&UserControlledClient::MouseCallback, this, std::placeholders::_1, std::placeholders::_2));
        rendering_manager->SetKeyboardCallback(std::bind(&UserControlledClient::KeyBoardCallback, this, std::placeholders::_1, std::placeholders::_2));
    }
#endif
}
