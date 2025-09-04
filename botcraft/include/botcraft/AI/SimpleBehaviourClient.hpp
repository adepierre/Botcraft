#pragma once

#include "botcraft/AI/TemplatedBehaviourClient.hpp"

namespace Botcraft
{
    /// @brief A client you can use if you only want to use behaviour trees and don't
    /// need to add any custom Handle functions. In case you need to react to packets,
    /// just inherit either this class, or BaseBehaviourClient the same way it's done here.
    class SimpleBehaviourClient : public TemplatedBehaviourClient<SimpleBehaviourClient>
    {
    public:
        SimpleBehaviourClient(const bool use_renderer_);

        virtual ~SimpleBehaviourClient();
    };
} // namespace Botcraft
