#include "botcraft/AI/BehaviourClient.hpp"

namespace Botcraft
{
    BehaviourClient::BehaviourClient(const bool use_renderer_) :
        ManagersClient(use_renderer_)
    {

    }

    BehaviourClient::~BehaviourClient()
    {

    }

    Blackboard& BehaviourClient::GetBlackboard()
    {
        return blackboard;
    }
} // namespace Botcraft
