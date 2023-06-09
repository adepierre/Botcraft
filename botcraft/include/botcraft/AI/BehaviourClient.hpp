#pragma once

#include "botcraft/Game/ManagersClient.hpp"
#include "botcraft/AI/Blackboard.hpp"

namespace Botcraft
{
    /// @brief A ManagersClient extended with a blackboard that can store any
    /// kind of data and a virtual Yield function.
    /// You should **not** inherit from this class, but from TemplatedBehaviourClient
    /// or SimpleBehaviourClient instead.
    class BehaviourClient : public ManagersClient, private BlackboardObserver
    {
    public:
        BehaviourClient(const bool use_renderer_);
        virtual ~BehaviourClient();

        virtual void Yield() = 0;

        Blackboard& GetBlackboard();

    public:
        void OnReset() override;
        void OnValueChanged(const std::string& key, const std::any& value) override;
        void OnValueRemoved(const std::string& key) override;

    protected:
        Blackboard blackboard;
    };
} // namespace Botcraft
