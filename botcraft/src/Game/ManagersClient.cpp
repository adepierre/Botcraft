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

        if (world && !world->IsShared())
        {
            world.reset();
        }
    }

    const int ManagersClient::GetDayTime() const
    {
        return day_time;
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

    std::shared_ptr<PhysicsManager> ManagersClient::GetPhysicsManager() const
    {
        return physics_manager;
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
            world = std::make_shared<World>(false, false);
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
        }
        physics_manager = std::make_shared<PhysicsManager>(rendering_manager, entity_manager, world, network_manager);
#else
        physics_manager = std::make_shared<PhysicsManager>(entity_manager, world, network_manager);
#endif
        physics_manager->StartPhysics();
    }

    void ManagersClient::Handle(ClientboundChangeDifficultyPacket &msg)
    {
        difficulty = static_cast<Difficulty>(msg.GetDifficulty());
#if PROTOCOL_VERSION > 463
        difficulty_locked = msg.GetLocked();
#endif
    }

    void ManagersClient::Handle(ClientboundLoginPacket &msg)
    {
        game_mode = static_cast<GameType>(msg.GetGameType() & 0x03);
#if PROTOCOL_VERSION > 737
        is_hardcore = msg.GetHardcore();
#else
        is_hardcore = msg.GetGameType() & 0x08;
#endif

#if PROTOCOL_VERSION < 464
        difficulty = static_cast<Difficulty>(msg.GetDifficulty());
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
        if (physics_manager)
        {
            physics_manager->SetHasGravity(!allow_flying);
        }

        std::shared_ptr<ServerboundClientInformationPacket> settings_msg = std::make_shared<ServerboundClientInformationPacket>();
        settings_msg->SetLanguage("fr_FR");
        settings_msg->SetViewDistance(10);
        settings_msg->SetChatVisibility(static_cast<int>(ChatMode::Enabled));
        settings_msg->SetChatColors(true);
        settings_msg->SetModelCustomisation(0xFF);
        settings_msg->SetMainHand(1); // 1 is right handed, 0 is left handed

        network_manager->Send(settings_msg);
    }

    void ManagersClient::Handle(ClientboundRespawnPacket &msg)
    {
#if PROTOCOL_VERSION < 464
        difficulty = static_cast<Difficulty>(msg.GetDifficulty());
#endif
        game_mode = static_cast<GameType>(msg.GetPlayerGameType());
    }

    void ManagersClient::Handle(ProtocolCraft::ClientboundSetTimePacket& msg)
    {
        // abs because the server multiplies by -1 when the sun will stop
        day_time = std::abs(msg.GetDayTime()) % 24000;
    }
} //Botcraft
