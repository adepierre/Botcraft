#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Biome.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/Game/ManagersClient.hpp"
#include "botcraft/Game/Physics/PhysicsManager.hpp"
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
        difficulty = Difficulty::None;
        is_hardcore = false;
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
        difficulty_locked = true;
#endif

        world = nullptr;
        inventory_manager = nullptr;
        entity_manager = nullptr;
        physics_manager = nullptr;

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
        std::thread::id network_process_thread_id;
        if (network_manager)
        {
            network_process_thread_id = network_manager->GetProcessingThreadId();
        }

        ConnectionClient::Disconnect();

        difficulty = Difficulty::None;
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
        difficulty_locked = true;
#endif
        is_hardcore = false;

        physics_manager.reset();
        entity_manager.reset();
        inventory_manager.reset();
#if USE_GUI
        if (rendering_manager)
        {
            rendering_manager->Close();
        }
        rendering_manager.reset();
#endif

        if (world)
        {
            world->UnloadAllChunks(network_process_thread_id);
            world.reset();
        }

        {
            std::scoped_lock<std::shared_mutex> lock(player_names_mutex);
            player_names.clear();
        }
    }

    int ManagersClient::GetDayTime() const
    {
        return day_time;
    }

    int ManagersClient::SendInventoryTransaction(const std::shared_ptr<ServerboundContainerClickPacket>& transaction)
    {
        InventoryTransaction inventory_transaction = inventory_manager->PrepareTransaction(transaction);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
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

    bool ManagersClient::GetAutoRespawn() const
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

    std::shared_ptr<LocalPlayer> ManagersClient::GetLocalPlayer() const
    {
        return entity_manager == nullptr ? nullptr : entity_manager->GetLocalPlayer();
    }

    std::shared_ptr<InventoryManager> ManagersClient::GetInventoryManager() const
    {
        return inventory_manager;
    }

    std::shared_ptr<PhysicsManager> ManagersClient::GetPhysicsManager() const
    {
        return physics_manager;
    }

    std::string ManagersClient::GetPlayerName(const UUID& uuid) const
    {
        std::shared_lock<std::shared_mutex> lock(player_names_mutex);
        auto it = player_names.find(uuid);
        if (it != player_names.end())
        {
            return it->second;
        }
        else if (entity_manager == nullptr || entity_manager->GetLocalPlayer() == nullptr)
        {
            return "";
        }
        else if (uuid == entity_manager->GetLocalPlayer()->GetUUID())
        {
            return network_manager->GetMyName();
        }
        return "";
    }


#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    void ManagersClient::Handle(ClientboundGameProfilePacket& packet)
#else
    void ManagersClient::Handle(ClientboundLoginFinishedPacket& packet)
#endif
    {
        // Create all handlers
        if (!world)
        {
            world = std::make_shared<World>(false);
        }

        inventory_manager = std::make_shared<InventoryManager>();
        entity_manager = std::make_shared<EntityManager>(network_manager);
        // Subscribe them to the network manager
        network_manager->AddHandler(world.get());
        network_manager->AddHandler(inventory_manager.get());
        network_manager->AddHandler(entity_manager.get());
#if USE_GUI
        if (use_renderer)
        {
            rendering_manager = std::make_shared<Renderer::RenderingManager>(world, inventory_manager, entity_manager, 800, 600, CHUNK_WIDTH, false);
            network_manager->AddHandler(rendering_manager.get());
        }
        physics_manager = std::make_shared<PhysicsManager>(rendering_manager, inventory_manager, entity_manager, network_manager, world);
#else
        physics_manager = std::make_shared<PhysicsManager>(inventory_manager, entity_manager, network_manager, world);
#endif
        network_manager->AddHandler(physics_manager.get());
        // Start physics
        physics_manager->StartPhysics();
    }

    void ManagersClient::Handle(ClientboundChangeDifficultyPacket& packet)
    {
        difficulty = static_cast<Difficulty>(packet.GetDifficulty());
#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
        difficulty_locked = packet.GetLocked();
#endif
    }

    void ManagersClient::Handle(ClientboundLoginPacket& packet)
    {
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        ConnectionClient::Handle(packet);
#endif

#if PROTOCOL_VERSION > 737 /* > 1.16.1 */
        is_hardcore = packet.GetHardcore();
#else
        is_hardcore = packet.GetGameType() & 0x08;
#endif

#if PROTOCOL_VERSION < 464 /* < 1.14 */
        difficulty = static_cast<Difficulty>(packet.GetDifficulty());
#endif
    }

    void ManagersClient::Handle(ClientboundSetHealthPacket& packet)
    {
        if (packet.GetHealth() <= 0.0f && auto_respawn)
        {
            Respawn();
        }
    }

    void ManagersClient::Handle(ClientboundPlayerPositionPacket& packet)
    {
        // Override the ConnectionClient Handle as the teleport confirmation is sent by the physics manager instead
    }

    void ManagersClient::Handle(ClientboundRespawnPacket& packet)
    {
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        ConnectionClient::Handle(packet);
#endif

#if PROTOCOL_VERSION < 464 /* < 1.14 */
        difficulty = static_cast<Difficulty>(packet.GetDifficulty());
#endif
    }

    void ManagersClient::Handle(ClientboundSetTimePacket& packet)
    {
        // abs because the server multiplies by -1 to indicate fixed daytime for versions < 1.21.2
        day_time = std::abs(packet.GetDayTime()) % 24000;
    }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    void ManagersClient::Handle(ClientboundPlayerInfoPacket& packet)
    {
        if (packet.GetAction() == PlayerInfoAction::RemovePlayer)
        {
            std::scoped_lock<std::shared_mutex> lock(player_names_mutex);
            for (const auto& [uuid, infos] : packet.GetEntries())
            {
                player_names.erase(uuid);
            }
        }
        else if (packet.GetAction() == PlayerInfoAction::AddPlayer)
        {
            std::scoped_lock<std::shared_mutex> lock(player_names_mutex);
            for (const auto& [uuid, infos] : packet.GetEntries())
            {
                if (infos.GetDisplayName().has_value())
                {
                    player_names[uuid] = infos.GetDisplayName().value().GetText();
                }
                else
                {
                    player_names[uuid] = infos.GetName();
                }
            }
        }
        else if (packet.GetAction() == PlayerInfoAction::UpdateDisplayName)
        {
            std::scoped_lock<std::shared_mutex> lock(player_names_mutex);
            for (const auto& [uuid, infos] : packet.GetEntries())
            {
                if (infos.GetDisplayName().has_value())
                {
                    player_names[uuid] = infos.GetDisplayName().value().GetText();
                }
            }
        }
    }
#else
    void ManagersClient::Handle(ClientboundPlayerInfoRemovePacket& packet)
    {
        std::scoped_lock<std::shared_mutex> lock(player_names_mutex);
        for (const auto& uuid : packet.GetProfileIds())
        {
            player_names.erase(uuid);
        }
    }

    void ManagersClient::Handle(ClientboundPlayerInfoUpdatePacket& packet)
    {
        for (const auto& action : packet.GetActions())
        {
            if (action == PlayerInfoUpdateAction::AddPlayer)
            {
                std::scoped_lock<std::shared_mutex> lock(player_names_mutex);
                for (const auto& [uuid, infos] : packet.GetEntries())
                {
                    player_names[uuid] = infos.game_profile.GetName();
                }
                continue;
            }
            if (action == PlayerInfoUpdateAction::UpdateDisplayName)
            {
                std::scoped_lock<std::shared_mutex> lock(player_names_mutex);
                for (const auto& [uuid, infos] : packet.GetEntries())
                {
                    if (infos.display_name.has_value())
                    {
                        player_names[uuid] = infos.display_name.value().GetText();
                    }
                }
            }
        }
    }
#endif
} //Botcraft
