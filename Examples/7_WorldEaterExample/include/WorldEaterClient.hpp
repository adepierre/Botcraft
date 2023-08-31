#pragma once

#include "botcraft/AI/SimpleBehaviourClient.hpp"

#include <string>

/// @brief Very simple extension of Botcraft::SimpleBehaviourClient.
/// The only addition is a Handle function to react to a specific
/// word in the chat, which will trigger the pause of the bots.
class WorldEaterClient : public Botcraft::SimpleBehaviourClient
{
public:
    WorldEaterClient(const std::string& trigger_word, const bool use_renderer_);
    ~WorldEaterClient();

protected:
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    virtual void Handle(ProtocolCraft::ClientboundChatPacket& msg) override;
#else
    virtual void Handle(ProtocolCraft::ClientboundPlayerChatPacket& msg) override;
    virtual void Handle(ProtocolCraft::ClientboundSystemChatPacket& msg) override;
#endif

    void ProcessChatMsg(const std::string& msg);

private:
    std::string word;
};
