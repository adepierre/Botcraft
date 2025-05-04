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
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundAddEntityPacket& packet) override;
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        virtual void Handle(ProtocolCraft::ClientboundAddMobPacket& packet) override;
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        virtual void Handle(ProtocolCraft::ClientboundAddExperienceOrbPacket& packet) override;
#endif
#if PROTOCOL_VERSION < 721 /* < 1.16 */
        virtual void Handle(ProtocolCraft::ClientboundAddGlobalEntityPacket& packet) override;
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        virtual void Handle(ProtocolCraft::ClientboundAddPlayerPacket& packet) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundTeleportEntityPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& packet) override;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacket& packet) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& packet) override;
#if PROTOCOL_VERSION == 755 /* 1.17 */
        virtual void Handle(ProtocolCraft::ClientboundRemoveEntityPacket& packet) override;
#else
        virtual void Handle(ProtocolCraft::ClientboundRemoveEntitiesPacket& packet) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundGameEventPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundSetEntityDataPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundSetEntityMotionPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundSetEquipmentPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundUpdateAttributesPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundUpdateMobEffectPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundRemoveMobEffectPacket& packet) override;
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        virtual void Handle(ProtocolCraft::ClientboundEntityPositionSyncPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveMinecartPacket& packet) override;
#endif


    private:
        std::unordered_map<int, std::shared_ptr<Entity> > entities;
        // The current player is stored independently
        std::shared_ptr<LocalPlayer> local_player;

        mutable std::shared_mutex entity_manager_mutex;

        std::shared_ptr<NetworkManager> network_manager;
    };
} // Botcraft