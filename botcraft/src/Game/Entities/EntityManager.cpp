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


    void EntityManager::Handle(ProtocolCraft::ClientboundLoginPacket& packet)
    {
        local_player = std::make_shared<LocalPlayer>();
        local_player->SetEntityID(packet.GetPlayerId());
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        local_player->SetGameMode(static_cast<GameType>(packet.GetGameType() & 0x03));
#else
        local_player->SetGameMode(static_cast<GameType>(packet.GetCommonPlayerSpawnInfo().GetGameType()));
#endif
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[packet.GetPlayerId()] = local_player;
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacket& packet)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        auto it = entities.find(packet.GetEntityId());
        if (it == entities.end())
        {
            std::shared_ptr<Entity> entity = std::make_shared<UnknownEntity>();
            entity->SetEntityID(packet.GetEntityId());
            entities[packet.GetEntityId()] = entity;
        }
    }
#endif

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
            const Vector3<double> entity_position = entity->GetPosition();
            entity->SetPosition(Vector3<double>(
                (packet.GetXA() / 128.0f + entity_position.x * 32.0f) / 32.0f,
                (packet.GetYA() / 128.0f + entity_position.y * 32.0f) / 32.0f,
                (packet.GetZA() / 128.0f + entity_position.z * 32.0f) / 32.0f
            ));
            entity->SetOnGround(packet.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
            const Vector3<double> entity_position = entity->GetPosition();
            entity->SetPosition(Vector3<double>(
                (packet.GetXA() / 128.0f + entity_position.x * 32.0f) / 32.0f,
                (packet.GetYA() / 128.0f + entity_position.y * 32.0f) / 32.0f,
                (packet.GetZA() / 128.0f + entity_position.z * 32.0f) / 32.0f
            ));
            entity->SetYaw(360.0f * packet.GetYRot() / 256.0f);
            entity->SetPitch(360.0f * packet.GetXRot() / 256.0f);
            entity->SetOnGround(packet.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
            entity->SetYaw(360.0f * packet.GetYRot() / 256.0f);
            entity->SetPitch(360.0f * packet.GetXRot() / 256.0f);
            entity->SetOnGround(packet.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundAddEntityPacket& packet)
    {
#if PROTOCOL_VERSION < 458 /* < 1.14 */
        std::shared_ptr<Entity> entity = Entity::CreateObjectEntity(static_cast<ObjectEntityType>(packet.GetType()));
#else
        std::shared_ptr<Entity> entity = Entity::CreateEntity(static_cast<EntityType>(packet.GetType()));
#endif

        entity->SetEntityID(packet.GetEntityId());
        entity->SetX(packet.GetX());
        entity->SetY(packet.GetY());
        entity->SetZ(packet.GetZ());
        entity->SetYaw(360.0f * packet.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * packet.GetXRot() / 256.0f);
        entity->SetUUID(packet.GetUuid());
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
        // Packet data is in 1/8000 of block per tick, so convert it back to block/tick
        entity->SetSpeed(Vector3<double>(packet.GetXa(), packet.GetYa(), packet.GetZa()) / 8000.0);
#else
        entity->SetSpeed(Vector3<double>(packet.GetMovement()));
#endif

        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[packet.GetEntityId()] = entity;
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundExplodePacket& packet)
    {

        std::shared_ptr<Entity> entity = local_player;

        if (entity == nullptr)
        {
            LOG_WARNING("Trying to apply knockback without a valid player");
        }
        else
        {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            entity->SetSpeed(entity->GetSpeed() + Vector3<double>(
                static_cast<double>(packet.GetKnockbackX()),
                static_cast<double>(packet.GetKnockbackY()),
                static_cast<double>(packet.GetKnockbackZ())
            ));
#else
            if (packet.GetPlayerKnockback().has_value())
            {
                entity->SetSpeed(entity->GetSpeed() + packet.GetPlayerKnockback().value());
            }
#endif
        }
    }

#if PROTOCOL_VERSION < 759 /* < 1.19 */
    void EntityManager::Handle(ProtocolCraft::ClientboundAddMobPacket& packet)
    {
        std::shared_ptr<Entity> entity = Entity::CreateEntity(static_cast<EntityType>(packet.GetType()));

        entity->SetEntityID(packet.GetEntityId());
        entity->SetX(packet.GetX());
        entity->SetY(packet.GetY());
        entity->SetZ(packet.GetZ());
        entity->SetYaw(360.0f * packet.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * packet.GetXRot() / 256.0f);
        entity->SetUUID(packet.GetUuid());

        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[packet.GetEntityId()] = entity;
    }
#endif

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void EntityManager::Handle(ProtocolCraft::ClientboundAddExperienceOrbPacket& packet)
    {
        std::shared_ptr<Entity> entity = Entity::CreateEntity(EntityType::ExperienceOrb);

        entity->SetEntityID(packet.GetEntityId());
        entity->SetX(packet.GetX());
        entity->SetY(packet.GetY());
        entity->SetZ(packet.GetZ());
        // What do we do with the xp value?
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[packet.GetEntityId()] = entity;
    }
#endif

#if PROTOCOL_VERSION < 721 /* < 1.16 */
    void EntityManager::Handle(ProtocolCraft::ClientboundAddGlobalEntityPacket& packet)
    {
        std::shared_ptr<Entity> entity = Entity::CreateEntity(static_cast<EntityType>(packet.GetType()));

        entity->SetEntityID(packet.GetEntityId());
        entity->SetX(packet.GetX());
        entity->SetY(packet.GetY());
        entity->SetZ(packet.GetZ());

        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities[packet.GetEntityId()] = entity;
    }
#endif

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    void EntityManager::Handle(ProtocolCraft::ClientboundAddPlayerPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
            if (it == entities.end())
            {
                entity = Entity::CreateEntity(EntityType::Player);
                entities[packet.GetEntityId()] = entity;
            }
            else
            {
                entity = it->second;
            }
        }

        entity->SetEntityID(packet.GetEntityId());
        entity->SetPosition(Vector3<double>(
            packet.GetX(),
            packet.GetY(),
            packet.GetZ()
        ));
        entity->SetYaw(360.0f * packet.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * packet.GetXRot() / 256.0f);
        entity->SetUUID(packet.GetPlayerId());
    }
#endif

    void EntityManager::Handle(ProtocolCraft::ClientboundSetHealthPacket& packet)
    {
        local_player->SetHealth(packet.GetHealth());
        local_player->SetFood(packet.GetFood());
        local_player->SetFoodSaturation(packet.GetFoodSaturation());
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundTeleportEntityPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            entity->SetPosition(Vector3<double>(
                packet.GetX(),
                packet.GetY(),
                packet.GetZ()
            ));
            entity->SetYaw(360.0f * packet.GetYRot() / 256.0f);
            entity->SetPitch(360.0f * packet.GetXRot() / 256.0f);
#else
            entity->SetPosition(Vector3<double>(
                packet.GetRelatives() & (1 << 0) ? entity->GetX() + packet.GetChange().GetPosition()[0] : packet.GetChange().GetPosition()[0],
                packet.GetRelatives() & (1 << 1) ? entity->GetY() + packet.GetChange().GetPosition()[1] : packet.GetChange().GetPosition()[1],
                packet.GetRelatives() & (1 << 2) ? entity->GetZ() + packet.GetChange().GetPosition()[2] : packet.GetChange().GetPosition()[2]
            ));
            entity->SetYaw(packet.GetRelatives() & (1 << 3) ? entity->GetYaw() + packet.GetChange().GetYRot() : packet.GetChange().GetYRot());
            entity->SetPitch(packet.GetRelatives() & (1 << 4) ? entity->GetPitch() + packet.GetChange().GetXRot() : packet.GetChange().GetXRot());
#endif
            entity->SetOnGround(packet.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& packet)
    {
        local_player->SetAbilitiesFlags(packet.GetFlags());
        local_player->SetFlyingSpeed(packet.GetFlyingSpeed());
        local_player->SetWalkingSpeed(packet.GetWalkingSpeed());
    }

#if PROTOCOL_VERSION == 755 /* 1.17 */
    void EntityManager::Handle(ProtocolCraft::ClientboundRemoveEntityPacket& packet)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        entities.erase(packet.GetEntityId());
    }
#else
    void EntityManager::Handle(ProtocolCraft::ClientboundRemoveEntitiesPacket& packet)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_manager_mutex);
        for (int i = 0; i < packet.GetEntityIds().size(); ++i)
        {
            entities.erase(packet.GetEntityIds()[i]);
        }
    }
#endif

    void EntityManager::Handle(ProtocolCraft::ClientboundRespawnPacket& packet)
    {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        local_player->SetGameMode(static_cast<GameType>(packet.GetPlayerGameType()));
#else
        local_player->SetGameMode(static_cast<GameType>(packet.GetCommonPlayerSpawnInfo().GetGameType()));
#endif
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundGameEventPacket& packet)
    {
        switch (packet.GetType())
        {
        case 3: // CHANGE_GAME_MODE
            local_player->SetGameMode(static_cast<GameType>(packet.GetParam()));
            break;
        default:
            break;
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundSetEntityDataPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
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
            entity->LoadMetadataFromRawArray(packet.GetPackedItems());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundSetEntityMotionPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
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
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
            // Packet data is in 1/8000 of block per tick, so convert it back to block/tick
            entity->SetSpeed(Vector3<double>(packet.GetXA(), packet.GetYA(), packet.GetZA()) / 8000.0);
#else
            entity->SetSpeed(Vector3<double>(packet.GetMovement()));
#endif
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundSetEquipmentPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
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
            for (auto& p : packet.GetSlots())
            {
                entity->SetEquipment(static_cast<EquipmentSlot>(p.first), p.second);
            }
#else
            entity->SetEquipment(static_cast<EquipmentSlot>(packet.GetSlot().first), packet.GetSlot().second);
#endif
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundUpdateAttributesPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
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
            for (const auto& a : packet.GetAttributes())
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

    void EntityManager::Handle(ProtocolCraft::ClientboundUpdateMobEffectPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
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
                static_cast<EntityEffectType>(packet.GetEffectId()), // type
                static_cast<unsigned char>(packet.GetEffectAmplifier()), //amplifier
                std::chrono::steady_clock::now() + std::chrono::milliseconds(50 * packet.GetEffectDurationTicks()) // end
            });
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundRemoveMobEffectPacket& packet)
    {

        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
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
            entity->RemoveEffect(static_cast<EntityEffectType>(packet.GetEffect()));
        }
    }

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    void EntityManager::Handle(ProtocolCraft::ClientboundEntityPositionSyncPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
            if (it != entities.end())
            {
                entity = it->second;
            }
        }

        if (entity != nullptr)
        {
            entity->SetPosition(packet.GetValues().GetPosition());
            if (entity == local_player)
            {
                return;
            }
            entity->SetYaw(packet.GetValues().GetYRot());
            entity->SetPitch(packet.GetValues().GetXRot());
            entity->SetOnGround(packet.GetOnGround());
        }
    }

    void EntityManager::Handle(ProtocolCraft::ClientboundMoveMinecartPacket& packet)
    {
        std::shared_ptr<Entity> entity = nullptr;

        {
            std::shared_lock<std::shared_mutex> lock(entity_manager_mutex);
            auto it = entities.find(packet.GetEntityId());
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

        const ProtocolCraft::MinecartBehaviorMinecartStep& step = packet.GetLerpSteps().back();
        entity->SetPosition(step.GetPosition());
        entity->SetYaw(360.0f * step.GetYRot() / 256.0f);
        entity->SetPitch(360.0f * step.GetXRot() / 256.0f);
    }
#endif
}
