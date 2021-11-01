#include "botcraft/AI/BehaviourClient.hpp"

namespace Botcraft
{
    BehaviourClient::BehaviourClient(const bool use_renderer_, const bool afk_only_) :
        BaseClient(use_renderer_, afk_only_)
    {

    }

    BehaviourClient::~BehaviourClient()
    {

    }

    Blackboard& BehaviourClient::GetBlackboard()
    {
        return blackboard;
    }

    void BehaviourClient::RemoveBlackboardEntries(const std::vector<std::string>& entries)
    {
        for (const auto& s : entries)
        {
            blackboard.Erase(s);
        }
    }
} // namespace Botcraft
