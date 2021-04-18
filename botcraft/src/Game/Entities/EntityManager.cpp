#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/Entity.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/Player.hpp"

#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

namespace Botcraft
{
    EntityManager::EntityManager()
    {
        local_player = std::shared_ptr<LocalPlayer>(new LocalPlayer);
    }

    std::shared_ptr<LocalPlayer> EntityManager::GetLocalPlayer()
    {
        return local_player;
    }

    const std::unordered_map<int, std::shared_ptr<Entity>>& EntityManager::GetEntities() const
    {
        return entities;
    }

#if USE_GUI
    void EntityManager::SetRenderingManager(std::shared_ptr<Renderer::RenderingManager> rendering_manager_)
    {
        rendering_manager = rendering_manager;
    }
#endif

    std::mutex& EntityManager::GetMutex()
    {
        return entity_manager_mutex;
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundLoginPacket& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        local_player = std::shared_ptr<LocalPlayer>(new LocalPlayer);
        local_player->GetMutex().lock();
        local_player->SetEID(msg.GetPlayerId());
        local_player->GetMutex().unlock();
        entities[msg.GetPlayerId()] = local_player;
    }
    
    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacket& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        auto it = entities.find(msg.GetEntityId());
        if (it == entities.end())
        {
            std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity);
            entity->SetEID(msg.GetEntityId());
            entities[msg.GetEntityId()] = entity;
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        // Player position is also used by physics thread, so we need
        // to lock it
        if (msg.GetEntityId() == local_player->GetEID())
        {
            local_player->GetMutex().lock();
        }
        
        auto it = entities.find(msg.GetEntityId());
        if (it != entities.end())
        {
            it->second->SetX((msg.GetXA() / 128.0f + it->second->GetPosition().x * 32.0f) / 32.0f);
            it->second->SetY((msg.GetYA() / 128.0f + it->second->GetPosition().y * 32.0f) / 32.0f);
            it->second->SetZ((msg.GetZA() / 128.0f + it->second->GetPosition().z * 32.0f) / 32.0f);
            it->second->SetOnGround(msg.GetOnGround());
        }
        
        if (msg.GetEntityId() == local_player->GetEID())
        {
#ifdef USE_GUI
            if (rendering_manager)
            {
                rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62f, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
            }
#endif // USE_GUI
            local_player->GetMutex().unlock();
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        // Player position is also used by physics thread, so we need
        // to lock it
        if (msg.GetEntityId() == local_player->GetEID())
        {
            local_player->GetMutex().lock();
        }

        auto it = entities.find(msg.GetEntityId());
        if (it != entities.end())
        {
            it->second->SetX((msg.GetXA() / 128.0f + it->second->GetPosition().x * 32.0f) / 32.0f);
            it->second->SetY((msg.GetYA() / 128.0f + it->second->GetPosition().y * 32.0f) / 32.0f);
            it->second->SetZ((msg.GetZA() / 128.0f + it->second->GetPosition().z * 32.0f) / 32.0f);
            it->second->SetYaw(360.0f * msg.GetYRot() / 256.0f);
            it->second->SetPitch(360.0f * msg.GetXRot() / 256.0f);
            it->second->SetOnGround(msg.GetOnGround());
        }

        if (msg.GetEntityId() == local_player->GetEID())
        {
#ifdef USE_GUI
            if (rendering_manager)
            {
                rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62f, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
            }
#endif // USE_GUI
            local_player->GetMutex().unlock();
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        // Player position is also used by physics thread, so we need
        // to lock it
        if (msg.GetEntityId() == local_player->GetEID())
        {
            local_player->GetMutex().lock();
        }

        auto it = entities.find(msg.GetEntityId());
        if (it != entities.end())
        {
            it->second->SetYaw(360.0f * msg.GetYRot() / 256.0f);
            it->second->SetPitch(360.0f * msg.GetXRot() / 256.0f);
            it->second->SetOnGround(msg.GetOnGround());
        }

        if (msg.GetEntityId() == local_player->GetEID())
        {
#ifdef USE_GUI
            if (rendering_manager)
            {
                rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62f, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
            }
#endif // USE_GUI
            local_player->GetMutex().unlock();
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundPlayerPositionPacket& msg)
    {
        std::lock_guard<std::mutex> player_guard(local_player->GetMutex());
        (msg.GetRelativeArguments() & 0x01) ? local_player->SetX(local_player->GetPosition().x + msg.GetX()) : local_player->SetX(msg.GetX());
        (msg.GetRelativeArguments() & 0x02) ? local_player->SetY(local_player->GetPosition().y + msg.GetY()) : local_player->SetY(msg.GetY());
        (msg.GetRelativeArguments() & 0x04) ? local_player->SetZ(local_player->GetPosition().z + msg.GetZ()) : local_player->SetZ(msg.GetZ());
        (msg.GetRelativeArguments() & 0x08) ? local_player->SetYaw(local_player->GetYaw() + msg.GetYRot()) : local_player->SetYaw(msg.GetYRot());
        (msg.GetRelativeArguments() & 0x10) ? local_player->SetPitch(local_player->GetPitch() + msg.GetXRot()) : local_player->SetPitch(msg.GetXRot());

#ifdef USE_GUI
        if (rendering_manager)
        {
            rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62f, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
        }
#endif // USE_GUI
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundAddEntityPacket& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        // TODO create the real entity type
        std::shared_ptr<Entity> entity;
        
        if (msg.GetType() == 106)
        {
            entity = std::shared_ptr<Player>(new Player);
        }
        else
        {
            entity = std::shared_ptr<Entity>(new Entity);
        }
        
        entity->SetEID(msg.GetId_());
        entity->SetX(msg.GetX());
        entity->SetY(msg.GetY());
        entity->SetZ(msg.GetZ());
        entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);

        entities[msg.GetId_()] = entity;
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundAddMobPacket& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        // TODO create the real entity type
        std::shared_ptr<Entity> entity;

        if (msg.GetType() == 106)
        {
            entity = std::shared_ptr<Player>(new Player);
        }
        else
        {
            entity = std::shared_ptr<Entity>(new Entity);
        }
        
        entity->SetEID(msg.GetId_());
        entity->SetX(msg.GetX());
        entity->SetY(msg.GetY());
        entity->SetZ(msg.GetZ());
        entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);

        entities[msg.GetId_()] = entity;
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundAddPlayerPacket& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);

        std::shared_ptr<Entity> entity;

        auto it = entities.find(msg.GetEntityId());
        if (it == entities.end())
        {
            std::cerr << "Warning, an unknown player entity is now in view" << std::endl;
            entity = std::shared_ptr<Player>(new Player);
            entities[msg.GetEntityId()] = entity;
        }
        else
        {
            entity = it->second;
        }

        entity->SetEID(msg.GetEntityId());
        entity->SetX(msg.GetX());
        entity->SetY(msg.GetY());
        entity->SetZ(msg.GetZ());
        entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundSetHealthPacket& msg)
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->SetHealth(msg.GetHealth());
        local_player->SetFood(msg.GetFood());
        local_player->SetFoodSaturation(msg.GetFoodSaturation());
    }
    
    void EntityManager::Handle(ProtocolCraft::ClientboundTeleportEntityPacket& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        if (msg.GetId_() == local_player->GetEID())
        {
            local_player->GetMutex().lock();
        }

        auto it = entities.find(msg.GetId_());
        if (it != entities.end())
        {
            it->second->SetX(msg.GetX());
            it->second->SetY(msg.GetY());
            it->second->SetZ(msg.GetZ());
            it->second->SetYaw(360.0f * msg.GetYRot() / 256.0f);
            it->second->SetPitch(360.0f * msg.GetXRot() / 256.0f);
            it->second->SetOnGround(msg.GetOnGround());
        }

        if (msg.GetId_() == local_player->GetEID())
        {
#ifdef USE_GUI
            if (rendering_manager)
            {
                rendering_manager->SetPosOrientation(local_player->GetPosition().x, local_player->GetPosition().y + 1.62f, local_player->GetPosition().z, local_player->GetYaw(), local_player->GetPitch());
            }
#endif // USE_GUI
            local_player->GetMutex().unlock();
        }
    }
    
    void EntityManager::Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& msg)
    {
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->SetIsInvulnerable(msg.GetFlags() & 0x01);
        local_player->SetIsFlying(msg.GetFlags() & 0x02);
        local_player->SetFlyingSpeed(msg.GetFlyingSpeed());

        //TODO do something with the walking speed
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundRemoveEntitiesPacket& msg)
    {
        std::lock_guard<std::mutex> entity_manager_locker(entity_manager_mutex);
        for (int i = 0; i < msg.GetEntityIds().size(); ++i)
        {
            entities.erase(msg.GetEntityIds()[i]);
        }
    }
}
