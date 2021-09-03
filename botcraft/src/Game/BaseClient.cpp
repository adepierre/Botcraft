#include <functional>
#include <iostream>

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/World/Biome.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/Game/BaseClient.hpp"

#include "botcraft/Network/NetworkManager.hpp"
#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

using namespace ProtocolCraft;

namespace Botcraft
{
    BaseClient::BaseClient(const bool use_renderer_, const bool afk_only_)
    {
        afk_only = afk_only_;
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
            std::cerr << "Warning, your version of botcraft hasn't been"
                << " compiled with GUI enabled, setting use_renderer_ to false" << std::endl;
        }
#endif
        auto_respawn = false;

        should_be_closed = false;

        // Ensure the assets are loaded
        AssetsManager::getInstance();
    }

    BaseClient::~BaseClient()
    {
        Disconnect();
    }

    void BaseClient::Connect(const std::string& address, const std::string& login, const std::string& password)
    {
        network_manager = std::shared_ptr<NetworkManager>(new NetworkManager(address, login, password));
        network_manager->AddHandler(this);
    }

    void BaseClient::RunSyncPos()
    {
        // Wait for 500 milliseconds before starting to send position continuously
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        auto last_send = std::chrono::system_clock::now();
        std::shared_ptr<ServerboundMovePlayerPacketPosRot> msg_position(new ServerboundMovePlayerPacketPosRot);
        bool has_moved = false;

        while (network_manager && network_manager->GetConnectionState() == ProtocolCraft::ConnectionState::Play)
        {
            // End of the current tick
            auto end = std::chrono::system_clock::now() + std::chrono::milliseconds(50);

            if (entity_manager)
            {
                std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
                if (local_player && local_player->GetPosition().y < 1000.0)
                {
                    if (afk_only)
                    {
                        has_moved = false;
                    }
                    else
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

                            //Avoid forever falling if position is <= 0.0
                            // TODO : not good with world extension
                            if (local_player->GetPosition().y <= 0.0)
                            {
                                local_player->SetY(0.0);
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
                    }

#if USE_GUI
                    if (rendering_manager && has_moved)
                    {
                        rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
                    }
#endif
                    if (network_manager &&
                        (has_moved || std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_send).count() >= 1000))
                    {
                        msg_position->SetX(local_player->GetPosition().x);
                        msg_position->SetY(local_player->GetPosition().y);
                        msg_position->SetZ(local_player->GetPosition().z);
                        msg_position->SetYRot(local_player->GetYaw());
                        msg_position->SetXRot(local_player->GetPitch());
                        msg_position->SetOnGround(local_player->GetOnGround());

                        network_manager->Send(msg_position);
                        last_send = std::chrono::system_clock::now();
                    }
                }
            }
            std::this_thread::sleep_until(end);
        }
    }

    void BaseClient::Physics(const bool is_in_fluid)
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

    const int BaseClient::SendInventoryTransaction(std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket> transaction)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager->GetMutex());
#if PROTOCOL_VERSION < 755
        std::shared_ptr<Window> window = inventory_manager->GetWindow(transaction->GetContainerId());
        if (!window)
        {
            std::cerr << "Warning, trying to set a transaction for an unknown window" << std::endl;
        }
        const int transaction_id = window->GetNextTransactionId();
        transaction->SetUid(transaction_id);
        window->SetNextTransactionId(transaction_id + 1);
        inventory_manager->AddPendingTransaction(transaction);

        network_manager->Send(transaction);
        return transaction_id;
#else
        const std::map<short, Slot> changed_slots = inventory_manager->ApplyTransaction(transaction);
        transaction->SetChangedSlots(changed_slots);
        network_manager->Send(transaction);
        return 1;
#endif
    }

    void BaseClient::Disconnect()
    {
        game_mode = GameType::None;
        difficulty = Difficulty::None;
#if PROTOCOL_VERSION > 463
        difficulty_locked = true;
#endif
        is_hardcore = false;

        network_manager.reset();
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

    void BaseClient::SetSharedWorld(const std::shared_ptr<World> world_)
    {
        world = world_;
    }

    void BaseClient::Handle(Message &msg)
    {

    }

    void BaseClient::Handle(ClientboundLoginDisconnectPacket &msg)
    {
        std::cout << "Disconnect during login with reason: " << 
            msg.GetReason().GetText() << std::endl;
        std::cout << "Disconnecting ..." << std::endl;

        should_be_closed = true;
    }

    void BaseClient::Handle(ClientboundGameProfilePacket &msg)
    {
        if (!world)
        {
            world = std::shared_ptr<World>(new World(false, false));
        }

        inventory_manager = std::shared_ptr<InventoryManager>(new InventoryManager);
        entity_manager = std::shared_ptr<EntityManager>(new EntityManager);

        if (!afk_only)
        {
            network_manager->AddHandler(world->GetAsyncHandler());
            network_manager->AddHandler(inventory_manager.get());
            network_manager->AddHandler(entity_manager.get());
        }

#if USE_GUI
        if (use_renderer)
        {
            rendering_manager = std::shared_ptr<Renderer::RenderingManager>(new Renderer::RenderingManager(world, inventory_manager, 800, 600, AssetsManager::getInstance().GetTexturesPathsNames(), CHUNK_WIDTH, false));
            if (!afk_only)
            {
                network_manager->AddHandler(rendering_manager.get());
            }
            entity_manager->SetRenderingManager(rendering_manager);
        }
#endif
        
        // Launch the physics thread (continuously sending the position to the server)
        m_thread_physics = std::thread(&BaseClient::RunSyncPos, this);
    }

    void BaseClient::Handle(ClientboundChangeDifficultyPacket &msg)
    {
        difficulty = (Difficulty)msg.GetDifficulty();
#if PROTOCOL_VERSION > 463
        difficulty_locked = msg.GetLocked();
#endif
    }

#if PROTOCOL_VERSION < 755
    void BaseClient::Handle(ClientboundContainerAckPacket &msg)
    {
        // If the transaction was not accepted, we must apologize
        // else it's processed in InventoryManager
        if (!msg.GetAccepted())
        {
            std::shared_ptr<ServerboundContainerAckPacket> apologize_msg(new ServerboundContainerAckPacket);
            apologize_msg->SetContainerId(msg.GetContainerId());
            apologize_msg->SetUid(msg.GetUid());
            apologize_msg->SetAccepted(msg.GetAccepted());

            network_manager->Send(apologize_msg);
        }
    }
#endif

    void BaseClient::Handle(ClientboundDisconnectPacket &msg)
    {
        std::cout << "Disconnect during playing with reason: " << 
            msg.GetReason().GetRawText() << std::endl;
        std::cout << "Disconnecting ..." << std::endl;
        
        should_be_closed = true;
    }

    void BaseClient::Handle(ClientboundLoginPacket &msg)
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

    void BaseClient::Handle(ClientboundPlayerPositionPacket& msg)
    {
        // Confirmations have to be sent from here
        // because EntityManager does not receive messages
        // in case of afk_only mode
        std::shared_ptr<ServerboundAcceptTeleportationPacket> confirm_msg(new ServerboundAcceptTeleportationPacket);
        confirm_msg->SetId_(msg.GetId_());

        network_manager->Send(confirm_msg);
    }

    void BaseClient::Handle(ClientboundSetHealthPacket &msg)
    {
        if (msg.GetHealth() <= 0.0f && auto_respawn)
        {
            std::shared_ptr<ServerboundClientCommandPacket> status_message(new ServerboundClientCommandPacket);
            status_message->SetAction(0);
            network_manager->Send(status_message);
        }
    }

    void BaseClient::Handle(ClientboundPlayerAbilitiesPacket &msg)
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

    void BaseClient::Handle(ClientboundRespawnPacket &msg)
    {
#if PROTOCOL_VERSION < 464
        difficulty = (Difficulty)msg.GetDifficulty();
#endif
        game_mode = (GameType)msg.GetPlayerGameType();
    }
} //Botcraft