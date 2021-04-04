#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/Entity.hpp"
#include "botcraft/Game/Entities/Player.hpp"

#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

namespace Botcraft
{
    EntityManager::EntityManager()
    {
        player = std::shared_ptr<Player>(new Player);
    }

    std::shared_ptr<Player> EntityManager::GetPlayer()
    {
        return player;
    }

#if USE_GUI
    void EntityManager::SetRenderingManager(std::shared_ptr<Renderer::RenderingManager> rendering_manager_)
    {
        rendering_manager = rendering_manager;
    }
#endif

    void EntityManager::Handle(ProtocolCraft::JoinGame& msg)
    {
        player = std::shared_ptr<Player>(new Player);
        player->GetMutex().lock();
        player->SetEID(msg.GetEntityId());
        player->GetMutex().unlock();
        entities[msg.GetEntityId()] = player;
    }
    
    void EntityManager::Handle(ProtocolCraft::EntityMovement& msg)
    {
        auto it = entities.find(msg.GetEntityId());
        if (it == entities.end())
        {
            std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity);
            entity->SetEID(msg.GetEntityId());
            entities[msg.GetEntityId()] = entity;
        }
    }

    void EntityManager::Handle(ProtocolCraft::EntityRelativeMove& msg)
    {
        // Player position is also used by physics thread, so we need
        // to lock it
        if (msg.GetEntityId() == player->GetEID())
        {
            player->GetMutex().lock();
        }
        
        auto it = entities.find(msg.GetEntityId());
        if (it != entities.end())
        {
            it->second->SetX((msg.GetDeltaX() / 128.0f + it->second->GetPosition().x * 32.0f) / 32.0f);
            it->second->SetY((msg.GetDeltaY() / 128.0f + it->second->GetPosition().y * 32.0f) / 32.0f);
            it->second->SetZ((msg.GetDeltaZ() / 128.0f + it->second->GetPosition().z * 32.0f) / 32.0f);
            it->second->SetOnGround(msg.GetOnGround());
        }
        
        if (msg.GetEntityId() == player->GetEID())
        {
#ifdef USE_GUI
            if (rendering_manager)
            {
                rendering_manager->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
            }
#endif // USE_GUI
            player->GetMutex().unlock();
        }
    }

    void EntityManager::Handle(ProtocolCraft::EntityLookAndRelativeMove& msg)
    {
        // Player position is also used by physics thread, so we need
        // to lock it
        if (msg.GetEntityId() == player->GetEID())
        {
            player->GetMutex().lock();
        }

        auto it = entities.find(msg.GetEntityId());
        if (it != entities.end())
        {
            it->second->SetY((msg.GetDeltaY() / 128.0f + it->second->GetPosition().y * 32.0f) / 32.0f);
            it->second->SetZ((msg.GetDeltaZ() / 128.0f + it->second->GetPosition().z * 32.0f) / 32.0f);
            it->second->SetX((msg.GetDeltaX() / 128.0f + it->second->GetPosition().x * 32.0f) / 32.0f);
            it->second->SetYaw(360.0f * msg.GetYaw() / 256.0f);
            it->second->SetPitch(360.0f * msg.GetPitch() / 256.0f);
            it->second->SetOnGround(msg.GetOnGround());
        }

        if (msg.GetEntityId() == player->GetEID())
        {
#ifdef USE_GUI
            if (rendering_manager)
            {
                rendering_manager->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
            }
#endif // USE_GUI
            player->GetMutex().unlock();
        }
    }

    void EntityManager::Handle(ProtocolCraft::EntityLook& msg)
    {
        // Player position is also used by physics thread, so we need
        // to lock it
        if (msg.GetEntityId() == player->GetEID())
        {
            player->GetMutex().lock();
        }

        auto it = entities.find(msg.GetEntityId());
        if (it != entities.end())
        {
            it->second->SetYaw(360.0f * msg.GetYaw() / 256.0f);
            it->second->SetPitch(360.0f * msg.GetPitch() / 256.0f);
            it->second->SetOnGround(msg.GetOnGround());
        }

        if (msg.GetEntityId() == player->GetEID())
        {
#ifdef USE_GUI
            if (rendering_manager)
            {
                rendering_manager->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
            }
#endif // USE_GUI
            player->GetMutex().unlock();
        }
    }

    void EntityManager::Handle(ProtocolCraft::PlayerPositionAndLookClientbound& msg)
    {
        std::lock_guard<std::mutex> player_guard(player->GetMutex());
        (msg.GetFlags() & 0x01) ? player->SetX(player->GetPosition().x + msg.GetX()) : player->SetX(msg.GetX());
        (msg.GetFlags() & 0x02) ? player->SetY(player->GetPosition().y + msg.GetY()) : player->SetY(msg.GetY());
        (msg.GetFlags() & 0x04) ? player->SetZ(player->GetPosition().z + msg.GetZ()) : player->SetZ(msg.GetZ());
        (msg.GetFlags() & 0x08) ? player->SetYaw(player->GetYaw() + msg.GetYaw()) : player->SetYaw(msg.GetYaw());
        (msg.GetFlags() & 0x10) ? player->SetPitch(player->GetPitch() + msg.GetPitch()) : player->SetPitch(msg.GetPitch());

#ifdef USE_GUI
        if (rendering_manager)
        {
            rendering_manager->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
        }
#endif // USE_GUI
    }

    void EntityManager::Handle(ProtocolCraft::UpdateHealth& msg)
    {
        std::lock_guard<std::mutex> player_lock(player->GetMutex());
        player->SetHealth(msg.GetHealth());
        player->SetFood(msg.GetFood());
        player->SetFoodSaturation(msg.GetFoodSaturation());
    }
    
    void EntityManager::Handle(ProtocolCraft::EntityTeleport& msg)
    {
        if (msg.GetEntityId() == player->GetEID())
        {
            player->GetMutex().lock();
        }

        auto it = entities.find(msg.GetEntityId());
        if (it != entities.end())
        {
            it->second->SetX(msg.GetX());
            it->second->SetY(msg.GetY());
            it->second->SetZ(msg.GetZ());
            it->second->SetYaw(360.0f * msg.GetYaw() / 256.0f);
            it->second->SetPitch(360.0f * msg.GetPitch() / 256.0f);
            it->second->SetOnGround(msg.GetOnGround());
        }

        if (msg.GetEntityId() == player->GetEID())
        {
#ifdef USE_GUI
            if (rendering_manager)
            {
                rendering_manager->SetPosOrientation(player->GetPosition().x, player->GetPosition().y + 1.62f, player->GetPosition().z, player->GetYaw(), player->GetPitch());
            }
#endif // USE_GUI
            player->GetMutex().unlock();
        }
    }
    
    void EntityManager::Handle(ProtocolCraft::PlayerAbilitiesClientbound& msg)
    {
        std::lock_guard<std::mutex> player_guard(player->GetMutex());
        player->SetIsInvulnerable(msg.GetFlags() & 0x01);
        player->SetIsFlying(msg.GetFlags() & 0x02);
        player->SetFlyingSpeed(msg.GetFlyingSpeed());

        //TODO do something with the field of view modifier
    }
}
