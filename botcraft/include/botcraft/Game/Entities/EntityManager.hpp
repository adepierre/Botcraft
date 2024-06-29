#pragma once

#include <memory>
#include <shared_mutex>
#include <unordered_map>

#include "protocolCraft/Handler.hpp"

#include "botcraft/Utilities/ScopeLockedWrapper.hpp"

namespace Botcraft
{
    class Entity;
    class LocalPlayer;
    class NetworkManager;

    class EntityManager : public ProtocolCraft::Handler
    {
    public:
        EntityManager(const std::shared_ptr<NetworkManager>& network_manager);

        std::shared_ptr<LocalPlayer> GetLocalPlayer();

        std::shared_ptr<Entity> GetEntity(const int id) const;
        void AddEntity(const std::shared_ptr<Entity>& entity);

        /// @brief Get a read-only locked version of all the loaded entities (including local player)
        /// @return Basically an object you can use as a std::unordered_map<int, std::shared_ptr<Entity>>*.
        /// **ALL ENTITIES UPDATE WILL BE BLOCKED WHILE THIS OBJECT IS ALIVE**, make sure it goes out of scope
        /// as soon as you don't need it.
        Utilities::ScopeLockedWrapper<const std::unordered_map<int, std::shared_ptr<Entity>>, std::shared_mutex, std::shared_lock> GetEntities() const;

    protected:
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundAddEntityPacket& msg) override;
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        virtual void Handle(ProtocolCraft::ClientboundAddMobPacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundAddExperienceOrbPacket& msg) override;
#if PROTOCOL_VERSION < 721 /* < 1.16 */
        virtual void Handle(ProtocolCraft::ClientboundAddGlobalEntityPacket& msg) override;
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        virtual void Handle(ProtocolCraft::ClientboundAddPlayerPacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundTeleportEntityPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& msg) override;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& msg) override;
#if PROTOCOL_VERSION == 755 /* 1.17 */
        virtual void Handle(ProtocolCraft::ClientboundRemoveEntityPacket& msg) override;
#else
        virtual void Handle(ProtocolCraft::ClientboundRemoveEntitiesPacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundGameEventPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetEntityDataPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetEntityMotionPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetEquipmentPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundUpdateAttributesPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundUpdateMobEffectPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundRemoveMobEffectPacket& msg) override;


    private:
        std::unordered_map<int, std::shared_ptr<Entity> > entities;
        // The current player is stored independently
        std::shared_ptr<LocalPlayer> local_player;

        mutable std::shared_mutex entity_manager_mutex;

        std::shared_ptr<NetworkManager> network_manager;
    };
} // Botcraft