#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/entities/Entity.hpp"
#include "botcraft/Game/Entities/entities/UnknownEntity.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Network/NetworkManager.hpp"

#include "botcraft/Utilities/Logger.hpp"

namespace Botcraft
{
    EntityManager::EntityManager(const std::shared_ptr<NetworkManager>& network_manager) : network_manager(network_manager)
    {
        local_player = nullptr;
    }

    std::shared_ptr<LocalPlayer> EntityManager::GetLocalPlayer()
    {
        return local_player;
    }

    std::shared_ptr<Entity> EntityManager::GetEntity(const int id) const
    {
        std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
        auto it = entities.find(id);
        return it == entities.end() ? nullptr : it->second;
    }

    void EntityManager::AddEntity(const std::shared_ptr<Entity>& entity)
    {
        if (entity == nullptr)
        {
            return;
        }

        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[entity->GetEntityID()] = entity;
    }

    Utilities::ScopeLockedWrapper<const std::unordered_map<int, std::shared_ptr<Entity>>, std::shared_mutex, std::shared_lock> EntityManager::GetEntities() const
    {
        return Utilities::ScopeLockedWrapper<const std::unordered_map<int, std::shared_ptr<Entity>>, std::shared_mutex, std::shared_lock>(entities, entity_manager_mutex);
    }


    void EntityManager::Handle(ProtocolCraft::ClientboundLoginPacket& msg)
    {
        local_player = std::make_shared<LocalPlayer>();
        local_player->SetEntityID(msg.GetPlayerId());
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        local_player->SetGameMode(static_cast<GameType>(msg.GetGameType() & 0x03));
#else
        local_player->SetGameMode(static_cast<GameType>(msg.GetCommonPlayerSpawnInfo().GetGameType()));
#endif
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[msg.GetPlayerId()] = local_player;
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacket& msg)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        auto it = entities.find(msg.GetEntityId());
        if (it == entities.end())
        {
            std::shared_ptr<Entity> entity = std::make_shared<UnknownEntity>();
            entity->SetEntityID(msg.GetEntityId());
            entities[msg.GetEntityId()] = entity;
        }
    }
#endif

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
            const Vector3<double> entity_position = entity->GetPosition();
            entity->SetPosition(Vector3<double>(
                (msg.GetXA() / 128.0f + entity_position.x * 32.0f) / 32.0f,
                (msg.GetYA() / 128.0f + entity_position.y * 32.0f) / 32.0f,
                (msg.GetZA() / 128.0f + entity_position.z * 32.0f) / 32.0f
            ));
            entity->SetOnGround(msg.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
            const Vector3<double> entity_position = entity->GetPosition();
            entity->SetPosition(Vector3<double>(
                (msg.GetXA() / 128.0f + entity_position.x * 32.0f) / 32.0f,
                (msg.GetYA() / 128.0f + entity_position.y * 32.0f) / 32.0f,
                (msg.GetZA() / 128.0f + entity_position.z * 32.0f) / 32.0f
            ));
            entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
            entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);
            entity->SetOnGround(msg.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
            entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
            entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);
            entity->SetOnGround(msg.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundAddEntityPacket& msg)
    {
#if PROTOCOL_VERSION < 458 /* < 1.14 */
        std::shared_ptr<Entity> entity = Entity::CreateObjectEntity(static_cast<ObjectEntityType>(msg.GetType()));
#else
        std::shared_ptr<Entity> entity = Entity::CreateEntity(static_cast<EntityType>(msg.GetType()));
#endif

        entity->SetEntityID(msg.GetEntityId());
        entity->SetX(msg.GetX());
        entity->SetY(msg.GetY());
        entity->SetZ(msg.GetZ());
        entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);
        entity->SetUUID(msg.GetUuid());

        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[msg.GetEntityId()] = entity;
    }

#if PROTOCOL_VERSION < 759 /* < 1.19 */
    void EntityManager::Handle(ProtocolCraft::ClientboundAddMobPacket& msg)
    {
        std::shared_ptr<Entity> entity = Entity::CreateEntity(static_cast<EntityType>(msg.GetType()));

        entity->SetEntityID(msg.GetEntityId());
        entity->SetX(msg.GetX());
        entity->SetY(msg.GetY());
        entity->SetZ(msg.GetZ());
        entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);
        entity->SetUUID(msg.GetUuid());

        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[msg.GetEntityId()] = entity;
    }
#endif

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void EntityManager::Handle(ProtocolCraft::ClientboundAddExperienceOrbPacket& msg)
    {
        std::shared_ptr<Entity> entity = Entity::CreateEntity(EntityType::ExperienceOrb);

        entity->SetEntityID(msg.GetEntityId());
        entity->SetX(msg.GetX());
        entity->SetY(msg.GetY());
        entity->SetZ(msg.GetZ());
        // What do we do with the xp value?
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[msg.GetEntityId()] = entity;
    }
#endif

#if PROTOCOL_VERSION < 721 /* < 1.16 */
    void EntityManager::Handle(ProtocolCraft::ClientboundAddGlobalEntityPacket& msg)
    {
        std::shared_ptr<Entity> entity = Entity::CreateEntity(static_cast<EntityType>(msg.GetType()));

        entity->SetEntityID(msg.GetEntityId());
        entity->SetX(msg.GetX());
        entity->SetY(msg.GetY());
        entity->SetZ(msg.GetZ());

        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[msg.GetEntityId()] = entity;
    }
#endif

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    void EntityManager::Handle(ProtocolCraft::ClientboundAddPlayerPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it == entities.end())
            {
                entity = Entity::CreateEntity(EntityType::Player);
                entities[msg.GetEntityId()] = entity;
            }
            else
            {
                entity = it->second;
            }
        }

        entity->SetEntityID(msg.GetEntityId());
        entity->SetPosition(Vector3<double>(
            msg.GetX(),
            msg.GetY(),
            msg.GetZ()
        ));
        entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);
        entity->SetUUID(msg.GetPlayerId());
    }
#endif

    void EntityManager::Handle(ProtocolCraft::ClientboundSetHealthPacket& msg)
    {
        local_player->SetHealth(msg.GetHealth());
        local_player->SetFood(msg.GetFood());
        local_player->SetFoodSaturation(msg.GetFoodSaturation());
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundTeleportEntityPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            entity->SetPosition(Vector3<double>(
                msg.GetX(),
                msg.GetY(),
                msg.GetZ()
            ));
            entity->SetYaw(360.0f * msg.GetYRot() / 256.0f);
            entity->SetPitch(360.0f * msg.GetXRot() / 256.0f);
#else
            entity->SetPosition(Vector3<double>(
                msg.GetRelatives() & (1 << 0) ? entity->GetX() + msg.GetChange().GetPosition()[0] : msg.GetChange().GetPosition()[0],
                msg.GetRelatives() & (1 << 1) ? entity->GetY() + msg.GetChange().GetPosition()[1] : msg.GetChange().GetPosition()[1],
                msg.GetRelatives() & (1 << 2) ? entity->GetZ() + msg.GetChange().GetPosition()[2] : msg.GetChange().GetPosition()[2]
            ));
            entity->SetYaw(msg.GetRelatives() & (1 << 3) ? entity->GetYaw() + msg.GetChange().GetYRot() : msg.GetChange().GetYRot());
            entity->SetPitch(msg.GetRelatives() & (1 << 4) ? entity->GetPitch() + msg.GetChange().GetXRot() : msg.GetChange().GetXRot());
#endif
            entity->SetOnGround(msg.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& msg)
    {
        local_player->SetAbilitiesFlags(msg.GetFlags());
        local_player->SetFlyingSpeed(msg.GetFlyingSpeed());
        local_player->SetWalkingSpeed(msg.GetWalkingSpeed());
    }

#if PROTOCOL_VERSION == 755 /* 1.17 */
    void EntityManager::Handle(ProtocolCraft::ClientboundRemoveEntityPacket& msg)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities.erase(msg.GetEntityId());
    }
#else
    void EntityManager::Handle(ProtocolCraft::ClientboundRemoveEntitiesPacket& msg)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        for (int i = 0; i < msg.GetEntityIds().size(); ++i)
        {
            entities.erase(msg.GetEntityIds()[i]);
        }
    }
#endif

    void EntityManager::Handle(ProtocolCraft::ClientboundRespawnPacket& msg)
    {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        local_player->SetGameMode(static_cast<GameType>(msg.GetPlayerGameType()));
#else
        local_player->SetGameMode(static_cast<GameType>(msg.GetCommonPlayerSpawnInfo().GetGameType()));
#endif
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundGameEventPacket& msg)
    {
        switch (msg.GetType())
        {
        case 3: // CHANGE_GAME_MODE
            local_player->SetGameMode(static_cast<GameType>(msg.GetParam()));
            break;
        default:
            break;
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundSetEntityDataPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity == nullptr)
        {
            LOG_WARNING("Trying to load metadata in unexisting entity");
        }
        else
        {
            entity->LoadMetadataFromRawArray(msg.GetPackedItems());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundSetEntityMotionPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity == nullptr)
        {
            LOG_WARNING("Trying to set speed of an unexisting entity");
        }
        else
        {
            // Packet data is in 1/8000 of block per tick, so convert it back to block/tick
            entity->SetSpeed(Vector3<double>(msg.GetXA(), msg.GetYA(), msg.GetZA()) / 8000.0);
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundSetEquipmentPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity == nullptr)
        {
            LOG_WARNING("Trying to set equipment of an unexisting entity");
        }
        else
        {
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
            for (auto& p : msg.GetSlots())
            {
                entity->SetEquipment(static_cast<EquipmentSlot>(p.first), p.second);
            }
#else
            entity->SetEquipment(static_cast<EquipmentSlot>(msg.GetSlot().first), msg.GetSlot().second);
#endif
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundUpdateAttributesPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity == nullptr)
        {
            LOG_WARNING("Trying to set attributes of an unexisting entity");
        }
        else if (!entity->IsLivingEntity())
        {
            LOG_WARNING("Trying to set attributes of a non LivingEntity");
        }
        else
        {
            std::shared_ptr<LivingEntity> living_entity = std::dynamic_pointer_cast<LivingEntity>(entity);
            for (const auto& a : msg.GetAttributes())
            {
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
                const EntityAttribute::Type type = static_cast<EntityAttribute::Type>(a.GetKey());
#elif PROTOCOL_VERSION > 709 /* > 1.15.2 */
                const EntityAttribute::Type type = EntityAttribute::StringToType(a.GetKey().GetFull());
#else
                const EntityAttribute::Type type = EntityAttribute::StringToType(a.GetKey());
#endif
                EntityAttribute attribute(type, a.GetValue());
                for (const auto& m : a.GetModifiers())
                {
                    attribute.SetModifier(
#if PROTOCOL_VERSION < 767 /* < 1.21 */
                        m.GetUuid(),
#else
                        m.GetId().GetFull(),
#endif
                        EntityAttribute::Modifier{ m.GetAmount(), static_cast<EntityAttribute::Modifier::Operation>(m.GetOperation()) }
                    );
                }
                living_entity->AddAttribute(attribute);
            }
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundUpdateMobEffectPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity == nullptr)
        {
            LOG_WARNING("Trying to set effect of an unexisting entity");
        }
        else
        {
            entity->AddEffect(EntityEffect {
                static_cast<EntityEffectType>(msg.GetEffectId()), // type
                static_cast<unsigned char>(msg.GetEffectAmplifier()), //amplifier
                std::chrono::steady_clock::now() + std::chrono::milliseconds(50 * msg.GetEffectDurationTicks()) // end
            });
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundRemoveMobEffectPacket& msg)
    {

        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity == nullptr)
        {
            LOG_WARNING("Trying to remove effect of an unexisting entity");
        }
        else
        {
            entity->RemoveEffect(static_cast<EntityEffectType>(msg.GetEffect()));
        }
    }

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    void EntityManager::Handle(ProtocolCraft::ClientboundEntityPositionSyncPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
            entity->SetPosition(msg.GetValues().GetPosition());
            if (entity == local_player)
            {
                return;
            }
            entity->SetYaw(msg.GetValues().GetYRot());
            entity->SetPitch(msg.GetValues().GetXRot());
            entity->SetOnGround(msg.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveMinecartPacket& msg)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(msg.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity == nullptr || !entity->IsAbstractMinecart())
        {
            return;
        }

        // Don't lerp, directly set the position to the last lerp step

        const ProtocolCraft::MinecartBehaviorMinecartStep& step = msg.GetLerpSteps().back();
        entity->SetPosition(step.GetPosition());
        entity->SetYaw(360.0f * step.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * step.GetXRot() / 256.0f);
    }
#endif
}
