#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/World/Biome.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/Game/ManagersClient.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"

#include "botcraft/Network/NetworkManager.hpp"
#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

using namespace ProtocolCraft;

namespace Botcraft
{
    ManagersClient::ManagersClient(const bool use_renderer_)
    {
        game_mode = GameType::None;
        difficulty = Difficulty::None;
        is_hardcore = false;
#if PROTOCOL_VERSION > 463
        difficulty_locked = true;
#endif

        world = nullptr;
        inventory_manager = nullptr;
        entity_manager = nullptr;

#if USE_GUI
        use_renderer = use_renderer_;
        rendering_manager = nullptr;
#else
        if (use_renderer_)
        {
            LOG_WARNING("Your version of botcraft hasn't been compiled with GUI enabled, setting use_renderer_ to false");
        }
#endif
        auto_respawn = false;

        // Ensure the assets are loaded
        AssetsManager::getInstance();
    }

    ManagersClient::~ManagersClient()
    {
        Disconnect();
    }

    void ManagersClient::Disconnect()
    {
        ConnectionClient::Disconnect();

        game_mode = GameType::None;
        difficulty = Difficulty::None;
#if PROTOCOL_VERSION > 463
        difficulty_locked = true;
#endif
        is_hardcore = false;

#if USE_GUI
        if (rendering_manager)
        {
            rendering_manager->Close();
        }
        rendering_manager.reset();
#endif

        if (m_thread_physics.joinable())
        {
            m_thread_physics.join();
        }

        if (world && !world->IsShared())
        {
            world.reset();
        }
        inventory_manager.reset();
        entity_manager.reset();
    }

    const int ManagersClient::GetDayTime() const
    {
        return day_time;
    }

    void ManagersClient::RunSyncPos()
    {
        Logger::GetInstance().RegisterThread("RunSyncPos");

        // Wait for 500 milliseconds before starting to send position continuously
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        auto last_send = std::chrono::steady_clock::now();
        std::shared_ptr<ServerboundMovePlayerPacketPosRot> msg_position(new ServerboundMovePlayerPacketPosRot);
        bool has_moved = false;

        while (network_manager && network_manager->GetConnectionState() == ProtocolCraft::ConnectionState::Play)
        {
            // End of the current tick
            auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(50);

            if (entity_manager)
            {
                std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
                if (local_player && local_player->GetPosition().y < 1000.0)
                {
                    bool is_loaded = false;
                    bool is_in_fluid = false;
                    std::lock_guard<std::mutex> player_guard(local_player->GetMutex());
                    {
                        std::lock_guard<std::mutex> mutex_guard(world->GetMutex());
                        const Position player_position = Position(std::floor(local_player->GetX()), std::floor(local_player->GetY()), std::floor(local_player->GetZ()));

                        is_loaded = world->IsLoaded(player_position);

                        if (is_loaded)
                        {
                            const Block* block_ptr = world->GetBlock(player_position);
                            is_in_fluid = block_ptr && block_ptr->GetBlockstate()->IsFluid();
                        }
                    }

                    if (is_loaded)
                    {
                        //Check that we did not go through a block
                        Physics(is_in_fluid);

                        if (local_player->GetHasMoved() ||
                            std::abs(local_player->GetSpeed().x) > 1e-3 ||
                            std::abs(local_player->GetSpeed().y) > 1e-3 ||
                            std::abs(local_player->GetSpeed().z) > 1e-3)
                        {
                            has_moved = true;
                            // Reset the player move state until next tick
                            local_player->SetHasMoved(false);
                        }
                        else
                        {
                            has_moved = false;
                        }

                        //Avoid forever falling if position is in the void
                        if (creative_mode && local_player->GetPosition().y <= world->GetMinY())
                        {
                            local_player->SetY(world->GetMinY());
                            local_player->SetSpeedY(0.0);
                            local_player->SetOnGround(true);
                        }

                        // Reset the speed until next frame
                        // Update the gravity value if needed
                        local_player->SetSpeedX(0.0);
                        local_player->SetSpeedZ(0.0);
                        if (local_player->GetOnGround())
                        {
                            local_player->SetSpeedY(0.0);
                        }
                        else
                        {
                            local_player->SetSpeedY((local_player->GetSpeed().y - 0.08) * 0.98);//TODO replace hardcoded value?
                        }
                    }

#if USE_GUI
                    if (rendering_manager && has_moved)
                    {
                        rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
                    }
#endif
                    if (network_manager &&
                        (has_moved || std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_send).count() >= 1000))
                    {
                        msg_position->SetX(local_player->GetPosition().x);
                        msg_position->SetY(local_player->GetPosition().y);
                        msg_position->SetZ(local_player->GetPosition().z);
                        msg_position->SetYRot(local_player->GetYaw());
                        msg_position->SetXRot(local_player->GetPitch());
                        msg_position->SetOnGround(local_player->GetOnGround());

                        network_manager->Send(msg_position);
                        last_send = std::chrono::steady_clock::now();
                    }
                }
            }
            SleepUntil(end);
        }
    }

    void ManagersClient::Physics(const bool is_in_fluid)
    {
        if (!entity_manager)
        {
            return;
        }

        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();

        //If the player did not move we assume it does not collide
        /*if (!local_player->GetHasMoved() &&
            abs(local_player->GetSpeed().x) < 1e-3 && 
            abs(local_player->GetSpeed().y) < 1e-3 && 
            abs(local_player->GetSpeed().z) < 1e-3)
        {
            // We could return if we were sure that we have a block under our feet
            return;
        }*/

        // Player mutex is already locked by calling function
        Position player_position(std::floor(local_player->GetX()), std::floor(local_player->GetY()), std::floor(local_player->GetX()));
        Vector3<double> min_player_collider, max_player_collider;
        for (int i = 0; i < 3; ++i)
        {
            min_player_collider[i] = std::min(local_player->GetCollider().GetMin()[i], local_player->GetCollider().GetMin()[i] + local_player->GetSpeed()[i]);
            max_player_collider[i] = std::max(local_player->GetCollider().GetMax()[i], local_player->GetCollider().GetMax()[i] + local_player->GetSpeed()[i]);
        }

        AABB broadphase_collider = AABB((min_player_collider + max_player_collider) / 2.0, (max_player_collider - min_player_collider) / 2.0);

        bool has_hit_down = false;
        bool has_hit_up = false;
        
        Position cube_pos;
        for (int x = (int)std::floor(min_player_collider.x); x < (int)std::ceil(max_player_collider.x); ++x)
        {
            cube_pos.x = x;
            for (int y = (int)std::floor(min_player_collider.y); y < (int)std::ceil(max_player_collider.y); ++y)
            {
                cube_pos.y = y;
                for (int z = (int)std::floor(min_player_collider.z); z < (int)std::ceil(max_player_collider.z); ++z)
                {
                    cube_pos.z = z;

                    Block block;
                    {
                        std::lock_guard<std::mutex> mutex_guard(world->GetMutex());
                        const Block *block_ptr = world->GetBlock(cube_pos);

                        if (block_ptr == nullptr)
                        {
                            continue;
                        }
                        block = *block_ptr;
                    }

                    if (!is_in_fluid && !block.GetBlockstate()->IsSolid())
                    {
                        continue;
                    }
                    
                    if (is_in_fluid &&
                        !block.GetBlockstate()->IsSolid() &&
                        (!block.GetBlockstate()->IsFluid() ||
                            cube_pos.y >= player_position.y))
                    {
                        continue;
                    }

                    const std::vector<AABB> &block_colliders = block.GetBlockstate()->GetModel(block.GetModelId()).GetColliders();

                    for (int i = 0; i < block_colliders.size(); ++i)
                    {
                        if (!broadphase_collider.Collide(block_colliders[i] + Vector3<double>(cube_pos.x, cube_pos.y, cube_pos.z)))
                        {
                            continue;
                        }

                        Vector3<double> normal;
                        const double speed_fraction = local_player->GetCollider().SweptCollide(local_player->GetSpeed(), block_colliders[i] + Vector3<double>(cube_pos.x, cube_pos.y, cube_pos.z), normal);

                        if (speed_fraction < 1.0)
                        {
                            const Vector3<double> remaining_speed = local_player->GetSpeed() * (1.0 - speed_fraction);

                            // We remove epsilon to be sure we do not go
                            // through the face due to numerical imprecision
                            local_player->SetSpeed(local_player->GetSpeed() * (speed_fraction - 1e-6) + // Base speed truncated
                                (remaining_speed - normal * remaining_speed.dot(normal))); // Remaining speed projected on the plane
                        }

                        if (normal.y == 1.0)
                        {
                            has_hit_down = true;
                        }
                        else if (normal.y == -1.0)
                        {
                            has_hit_up = true;
                        }

                    }
                }
            }
        }
        local_player->SetPosition(local_player->GetPosition() + local_player->GetSpeed());
        local_player->SetOnGround(has_hit_down);
        if (has_hit_up)
        {
            local_player->SetSpeedY(0.0);
        }
    }

    const int ManagersClient::SendInventoryTransaction(const std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket>& transaction)
    {
        InventoryTransaction inventory_transaction = inventory_manager->PrepareTransaction(transaction);
#if PROTOCOL_VERSION < 755
        inventory_manager->AddPendingTransaction(inventory_transaction);
        network_manager->Send(transaction);
        return transaction->GetUid();
#else
        network_manager->Send(transaction);
        // In 1.17+ there is no server confirmation so apply it directly
        inventory_manager->ApplyTransaction(inventory_transaction);
        return 1;
#endif
    }

    void ManagersClient::SetSharedWorld(const std::shared_ptr<World> world_)
    {
        world = world_;
    }

    const bool ManagersClient::GetAutoRespawn() const
    {
        return auto_respawn;
    }

    void ManagersClient::SetAutoRespawn(const bool b)
    {
        auto_respawn = b;
    }

    std::shared_ptr<World> ManagersClient::GetWorld() const
    {
        return world;
    }

    std::shared_ptr<EntityManager> ManagersClient::GetEntityManager() const
    {
        return entity_manager;
    }

    std::shared_ptr<InventoryManager> ManagersClient::GetInventoryManager() const
    {
        return inventory_manager;
    }

    const bool ManagersClient::GetCreativeMode() const
    {
        return creative_mode;
    }

    void ManagersClient::Handle(Message &msg)
    {

    }

    void ManagersClient::Handle(ClientboundGameProfilePacket &msg)
    {
        if (!world)
        {
            world = std::shared_ptr<World>(new World(false, false));
        }

        inventory_manager = std::make_shared<InventoryManager>();
        entity_manager = std::make_shared<EntityManager>();

        network_manager->AddHandler(world->GetAsyncHandler());
        network_manager->AddHandler(inventory_manager.get());
        network_manager->AddHandler(entity_manager.get());

#if USE_GUI
        if (use_renderer)
        {
            rendering_manager = std::make_shared<Renderer::RenderingManager>(world, inventory_manager, entity_manager, 800, 600, CHUNK_WIDTH, false);
            network_manager->AddHandler(rendering_manager.get());
            entity_manager->SetRenderingManager(rendering_manager);
        }
#endif
        
        // Launch the physics thread (continuously sending the position to the server)
        m_thread_physics = std::thread(&ManagersClient::RunSyncPos, this);
    }

    void ManagersClient::Handle(ClientboundChangeDifficultyPacket &msg)
    {
        difficulty = (Difficulty)msg.GetDifficulty();
#if PROTOCOL_VERSION > 463
        difficulty_locked = msg.GetLocked();
#endif
    }

    void ManagersClient::Handle(ClientboundLoginPacket &msg)
    {
        game_mode = (GameType)(msg.GetGameType() & 0x03);
#if PROTOCOL_VERSION > 737
        is_hardcore = msg.GetHardcore();
#else
        is_hardcore = msg.GetGameType() & 0x08;
#endif

#if PROTOCOL_VERSION < 464
        difficulty = (Difficulty)msg.GetDifficulty();
#endif
    }

    void ManagersClient::Handle(ClientboundSetHealthPacket& msg)
    {
        if (msg.GetHealth() <= 0.0f && auto_respawn)
        {
            std::shared_ptr<ServerboundClientCommandPacket> status_message(new ServerboundClientCommandPacket);
            status_message->SetAction(0);
            network_manager->Send(status_message);
        }
    }

    void ManagersClient::Handle(ClientboundPlayerAbilitiesPacket &msg)
    {
        allow_flying = msg.GetFlags() & 0x04;
        creative_mode = msg.GetFlags() & 0x08;

        std::shared_ptr<ServerboundClientInformationPacket> settings_msg(new ServerboundClientInformationPacket);
        settings_msg->SetLanguage("fr_FR");
        settings_msg->SetViewDistance(10);
        settings_msg->SetChatVisibility((int)ChatMode::Enabled);
        settings_msg->SetChatColors(true);
        settings_msg->SetModelCustomisation(0xFF);
        settings_msg->SetMainHand((int)Hand::Right);

        network_manager->Send(settings_msg);
    }

    void ManagersClient::Handle(ClientboundRespawnPacket &msg)
    {
#if PROTOCOL_VERSION < 464
        difficulty = (Difficulty)msg.GetDifficulty();
#endif
        game_mode = (GameType)msg.GetPlayerGameType();
    }

    void ManagersClient::Handle(ProtocolCraft::ClientboundSetTimePacket& msg)
    {
        day_time = msg.GetDayTime() % 24000;
    }
} //Botcraft
