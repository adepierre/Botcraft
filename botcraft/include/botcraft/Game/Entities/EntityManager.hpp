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
        virtual void Handle(ProtocolCraft::JoinGame& msg) override;
        virtual void Handle(ProtocolCraft::PlayerPositionAndLookClientbound& msg) override;
        virtual void Handle(ProtocolCraft::SpawnObject& msg) override;
        virtual void Handle(ProtocolCraft::SpawnPlayer& msg) override;



        virtual void Handle(ProtocolCraft::UpdateHealth& msg) override;
        virtual void Handle(ProtocolCraft::EntityTeleport& msg) override;
        virtual void Handle(ProtocolCraft::PlayerAbilitiesClientbound& msg) override;
        virtual void Handle(ProtocolCraft::EntityMovement& msg) override;
        virtual void Handle(ProtocolCraft::EntityRelativeMove& msg) override;
        virtual void Handle(ProtocolCraft::EntityLookAndRelativeMove& msg) override;
        virtual void Handle(ProtocolCraft::EntityLook& msg) override;


    private:
        std::unordered_map<int, std::shared_ptr<Entity> > entities;
        // The current player is stored independently
        std::shared_ptr<LocalPlayer> local_player;

#if USE_GUI
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif
    };
} // Botcraft