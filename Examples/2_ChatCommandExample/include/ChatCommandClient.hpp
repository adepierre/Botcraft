#pragma once

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/AI/TemplatedBehaviourClient.hpp"

/// @brief Example of a class where we inherit
/// TemplatedBehaviourClient<T>, with this class as parameter.
/// We can then use Behaviour Trees with this class as
/// context, and do our stuff. We also override on Handle function
class ChatCommandClient : public Botcraft::TemplatedBehaviourClient<ChatCommandClient>
{
public:
    ChatCommandClient(const bool use_renderer_);
    ~ChatCommandClient();

protected:
#if PROTOCOL_VERSION < 759
    virtual void Handle(ProtocolCraft::ClientboundChatPacket &msg) override;
#else
    virtual void Handle(ProtocolCraft::ClientboundPlayerChatPacket& msg) override;
    virtual void Handle(ProtocolCraft::ClientboundSystemChatPacket& msg) override;
#endif

    void ProcessChatMsg(const std::vector<std::string>& splitted_msg);

    // Check for any spawnable blocks in a sphere from pos and prints
    // all the positions into a file
    // Use check_lighting to add a check on light block value (> 7)
    // (warning: ignore top slabs and upside-down stairs,
    // you should check for such blocks manually)
    void CheckPerimeter(const Botcraft::Position &pos, const float radius, const bool check_lighting);
};
