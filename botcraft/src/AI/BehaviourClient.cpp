#include "botcraft/AI/BehaviourClient.hpp"
#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

namespace Botcraft
{
    BehaviourClient::BehaviourClient(const bool use_renderer_) :
        ManagersClient(use_renderer_)
    {
        blackboard.Subscribe(this);
    }

    BehaviourClient::~BehaviourClient()
    {
        blackboard.Unsubscribe(this);
    }

    Blackboard& BehaviourClient::GetBlackboard()
    {
        return blackboard;
    }

    void BehaviourClient::OnReset() const
    {
#if USE_GUI
        if (rendering_manager != nullptr)
        {
            rendering_manager->ResetBlackboard();
        }
#endif
    }

    void BehaviourClient::OnValueChanged(const std::string& key, const std::any& value) const
    {
#if USE_GUI
        if (rendering_manager != nullptr)
        {
            rendering_manager->UpdateBlackboardValue(key, value);
        }
#endif
    }

    void BehaviourClient::OnValueRemoved(const std::string& key) const
    {
#if USE_GUI
        if (rendering_manager != nullptr)
        {
            rendering_manager->RemoveBlackboardValue(key);
        }
#endif
    }
} // namespace Botcraft
