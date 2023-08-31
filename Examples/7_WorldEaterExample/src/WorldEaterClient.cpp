#include <botcraft/AI/Tasks/BaseTasks.hpp>
#include <botcraft/AI/Tasks/PathfindingTask.hpp>
#include <botcraft/Game/Vector3.hpp>

#include "WorldEaterClient.hpp"

using namespace Botcraft;

WorldEaterClient::WorldEaterClient(const std::string& trigger_word, const bool use_renderer_) : SimpleBehaviourClient(use_renderer_)
{
    word = trigger_word;
}

WorldEaterClient::~WorldEaterClient()
{

}

#if PROTOCOL_VERSION < 759 /* < 1.19 */
void WorldEaterClient::Handle(ProtocolCraft::ClientboundChatPacket& msg)
{
    ManagersClient::Handle(msg);

    ProcessChatMsg(msg.GetMessage().GetText());
}
#else
void WorldEaterClient::Handle(ProtocolCraft::ClientboundPlayerChatPacket& msg)
{
    ManagersClient::Handle(msg);

#if PROTOCOL_VERSION == 759 /* 1.19 */
    ProcessChatMsg(msg.GetSignedContent().GetText());
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
    ProcessChatMsg(msg.GetMessage_().GetSignedBody().GetContent().GetPlain());
#else
    ProcessChatMsg(msg.GetBody().GetContent());
#endif
}

void WorldEaterClient::Handle(ProtocolCraft::ClientboundSystemChatPacket& msg)
{
    ManagersClient::Handle(msg);

    ProcessChatMsg(msg.GetContent().GetText());
}
#endif

void WorldEaterClient::ProcessChatMsg(const std::string& msg)
{
    if (msg != word)
    {
        return;
    }

    Position out_position;
    try
    {
        out_position = blackboard.Get<Position>("Eater.out_position");
    }
    catch (const std::exception&)
    {
        // Probably not initialized yet, do nothing except warn user
        LOG_WARNING("out_position not found in the blackboard, can't abort. Is the bot initialized?");
        return;
    }

    const std::string& bot_name = network_manager->GetMyName();

    SetBehaviourTree(Builder<SimpleBehaviourClient>("Completion Tree")
        .sequence()
            .leaf("Go to out pos", GoTo, out_position + Position(0, 1, 0), 0, 0, 0, 0.0f, true)
            .leaf("Notify", Say, network_manager->GetMyName() + " out")
            .leaf("Set should be closed", [](SimpleBehaviourClient& c) { c.SetShouldBeClosed(true); return Status::Success; })
            .leaf("Set null tree", [](SimpleBehaviourClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
        .end());
}
