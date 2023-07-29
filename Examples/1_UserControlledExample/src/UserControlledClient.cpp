#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Version.hpp"
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
        world = std::make_shared<World>(false, false);
        entity_manager = std::make_shared<EntityManager>();

        should_be_closed = false;
        creative_mode = true;

#ifdef USE_GUI
        if (use_renderer)
        {
            rendering_manager = std::make_shared<Renderer::RenderingManager>(world, inventory_manager, entity_manager, 800, 600, CHUNK_WIDTH, false);
            mouse_sensitivity = 0.1f;

            rendering_manager->SetMouseCallback(std::bind(&UserControlledClient::MouseCallback, this, std::placeholders::_1, std::placeholders::_2));
            rendering_manager->SetKeyboardCallback(std::bind(&UserControlledClient::KeyBoardCallback, this, std::placeholders::_1, std::placeholders::_2));
        }
        physics_manager = std::make_shared<PhysicsManager>(rendering_manager, entity_manager, world, network_manager);
#else
        physics_manager = std::make_shared<PhysicsManager>(entity_manager, world, network_manager);
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
#if PROTOCOL_VERSION < 719
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif

#if PROTOCOL_VERSION > 756
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
        const Biome* biome = AssetsManager::getInstance().GetBiome(i);
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
            const Blockstate* previous_blockstate;
            if (block != nullptr)
            {
                previous_blockstate = block->GetBlockstate();
            }
            else
            {
#if PROTOCOL_VERSION < 347
                previous_blockstate = AssetsManager::getInstance().Blockstates().at(0).at(0).get();
#else
                previous_blockstate = AssetsManager::getInstance().Blockstates().at(0).get();
#endif
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
            }
            else
            {
#if PROTOCOL_VERSION < 347
                previous_blockstate = AssetsManager::getInstance().Blockstates().at(0).at(0).get();
#else
                previous_blockstate = AssetsManager::getInstance().Blockstates().at(0).get();
#endif
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
    local_player->SetYaw(static_cast<float>(local_player->GetYaw() + xoffset * mouse_sensitivity));

    rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62f, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
}

void UserControlledClient::KeyBoardCallback(const std::array<bool, static_cast<int>(Renderer::KEY_CODE::NUMBER_OF_KEYS)> &is_key_pressed, const double &delta_time)
{
    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();

    bool pos_has_changed = false;
    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::ESC)])
    {
        should_be_closed = true;
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::SPACE)])
    {
        if (local_player->GetOnGround() && !local_player->GetIsClimbing())
        {
            // Jump
            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
            local_player->Jump();
        }
        else if (local_player->GetIsClimbing())
        {
            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
            local_player->AddPlayerInputsY(2.0 * delta_time);
        }
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::CTRL)])
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->AddPlayerInputsY(-2.0 * delta_time);
    }

    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->SetIsRunning(is_key_pressed[static_cast<int>(Renderer::KEY_CODE::SHIFT)]);
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::FORWARD)])
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->AddPlayerInputsX(local_player->GetXZVector().x * (local_player->GetIsRunning() ? 5.612 : LocalPlayer::WALKING_SPEED) * delta_time);
        local_player->AddPlayerInputsZ(local_player->GetXZVector().z * (local_player->GetIsRunning() ? 5.612 : LocalPlayer::WALKING_SPEED) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::BACKWARD)])
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->AddPlayerInputsX(- local_player->GetXZVector().x * (local_player->GetIsRunning() ? LocalPlayer::SPRINTING_SPEED : LocalPlayer::WALKING_SPEED) * delta_time);
        local_player->AddPlayerInputsZ(- local_player->GetXZVector().z * (local_player->GetIsRunning() ? LocalPlayer::SPRINTING_SPEED : LocalPlayer::WALKING_SPEED) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::RIGHT)])
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->AddPlayerInputsX(local_player->GetRightVector().x * (local_player->GetIsRunning() ? LocalPlayer::SPRINTING_SPEED : LocalPlayer::WALKING_SPEED) * delta_time);
        local_player->AddPlayerInputsZ(local_player->GetRightVector().z * (local_player->GetIsRunning() ? LocalPlayer::SPRINTING_SPEED : LocalPlayer::WALKING_SPEED) * delta_time);

        pos_has_changed = true;
    }

    if (is_key_pressed[static_cast<int>(Renderer::KEY_CODE::LEFT)])
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->AddPlayerInputsX(- local_player->GetRightVector().x * (local_player->GetIsRunning() ? LocalPlayer::SPRINTING_SPEED : LocalPlayer::WALKING_SPEED) * delta_time);
        local_player->AddPlayerInputsZ(- local_player->GetRightVector().z * (local_player->GetIsRunning() ? LocalPlayer::SPRINTING_SPEED : LocalPlayer::WALKING_SPEED) * delta_time);

        pos_has_changed = true;
    }

    if (pos_has_changed)
    {
        rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
    }
}
#endif

void UserControlledClient::Handle(ClientboundGameProfilePacket &msg)
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
