#pragma once

#include <botcraft/Game/Vector3.hpp>
#include <botcraft/AI/TemplatedBehaviourClient.hpp>

/// <summary>
/// Example of a class where we need to add a Handle function
/// for specific packet processing. In this case we can inherit
/// BaseBehaviourClient<T>, with this class as parameter.
/// We can then use Behaviour Trees with this class as
/// context, and do our stuff.
/// </summary>
class ChatCommandClient : public Botcraft::TemplatedBehaviourClient<ChatCommandClient>
{
public:
    ChatCommandClient(const bool use_renderer_);
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
