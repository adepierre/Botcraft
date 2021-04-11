#pragma once

#include "protocolCraft/Handler.hpp"
#include <unordered_map>
#include <memory>

namespace Botcraft
{
    class Entity;
    class LocalPlayer;

#if USE_GUI
    namespace Renderer
    {
        class RenderingManager;
    }
#endif

    class EntityManager : public ProtocolCraft::Handler
    {
    public:
        EntityManager();

        std::shared_ptr<LocalPlayer> GetLocalPlayer();
#if USE_GUI
        void SetRenderingManager(std::shared_ptr<Renderer::RenderingManager> rendering_manager_);
#endif

    protected:
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerPositionPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundAddMobPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundAddPlayerPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundTeleportEntityPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPos& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketPosRot& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundMoveEntityPacketRot& msg) override;


    private:
        std::unordered_map<int, std::shared_ptr<Entity> > entities;
        // The current player is stored independently
        std::shared_ptr<LocalPlayer> local_player;

#if USE_GUI
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif
    };
} // Botcraft