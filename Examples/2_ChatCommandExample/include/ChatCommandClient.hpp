#pragma once

#include <botcraft/Game/Vector3.hpp>
#include <botcraft/AI/InterfaceClient.hpp>

class ChatCommandClient : public Botcraft::InterfaceClient
{
public:
    ChatCommandClient(const bool use_renderer_, const bool is_afk_);
    ~ChatCommandClient();

protected:
    virtual void Handle(ProtocolCraft::ClientboundChatPacket &msg) override;

    // Check for any spawnable blocks in a sphere from pos and prints
    // all the positions into a file
    // Use check_lighting to add a check on light block value (> 7)
    // (warning: ignore top slabs and upside-down stairs,
    // you should check for such blocks manually)
    void CheckPerimeter(const Botcraft::Position &pos, const float radius, const bool check_lighting);
};