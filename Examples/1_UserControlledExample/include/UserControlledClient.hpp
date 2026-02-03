#pragma once

#include "botcraft/Game/ManagersClient.hpp"

#include "botcraft/Renderer/RenderingManager.hpp"

class UserControlledClient : public Botcraft::ManagersClient
{
public:
    UserControlledClient(bool online, bool use_renderer_, std::pair<int, int> resolution);
    ~UserControlledClient();

protected:

#ifdef USE_GUI
    void MouseCallback(const double& xoffset, const double& yoffset);
    void KeyBoardCallback(const std::array<bool, static_cast<int>(Botcraft::Renderer::KEY_CODE::NUMBER_OF_KEYS)>& is_key_pressed, const double& delta_time);
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    virtual void Handle(ProtocolCraft::ClientboundGameProfilePacket& msg) override;
#else
    virtual void Handle(ProtocolCraft::ClientboundLoginFinishedPacket& msg) override;
#endif

    void CreateTestWorld();

protected:

#if USE_GUI
    float mouse_sensitivity;
#endif
};
