#pragma once

#include "protocolCraft/Handler.hpp"
#include <unordered_map>
#include <memory>
#include <mutex>

namespace Botcraft
{
    class Entity;
    class LocalPlayer;

    class EntityManager : public ProtocolCraft::Handler
    {
    public:
        EntityManager();

        std::shared_ptr<LocalPlayer> GetLocalPlayer();
        const std::unordered_map<int, std::shared_ptr<Entity> >& GetEntities() const;
        std::shared_ptr<Entity> GetEntity(const int id) const;
        void AddEntity(const std::shared_ptr<Entity>& entity);

        std::mutex& GetMutex();

    protected:
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerPositionPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundAddEntityPacket& msg) override;
#if PROTOCOL_VERSION < 759
        virtual void Handle(ProtocolCraft::ClientboundAddMobPacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundAddExperienceOrbPacket& msg) override;
#if PROTOCOL_VERSION < 721
        virtual void Handle(ProtocolCraft::ClientboundAddGlobalEntityPacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundAddPlayerPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundTeleportEntityPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& msg) override;
#if PROTOCOL_VERSION < 755
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& msg) override;
#if PROTOCOL_VERSION == 755
        virtual void Handle(ProtocolCraft::ClientboundRemoveEntityPacket& msg) override;
#else
        virtual void Handle(ProtocolCraft::ClientboundRemoveEntitiesPacket& msg) override;
#endif
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

        std::mutex entity_manager_mutex;
    };
} // Botcraft