#pragma once

#include <botcraft/AI/BaseBehaviourClient.hpp>

namespace Botcraft
{
    namespace AI
    {
        /// @brief A client you can use if you only want to use behaviour trees and don't
        /// need to add any custom Handle functions. In case you need to react to packets,
        /// just inherit either this class, or BaseBehaviourClient the same way it's done here.
        class SimpleBehaviourClient : public Botcraft::AI::BaseBehaviourClient<SimpleBehaviourClient>
        {
        public:
            SimpleBehaviourClient(const bool use_renderer_, const bool is_afk_ = false) : Botcraft::AI::BaseBehaviourClient<SimpleBehaviourClient>(use_renderer_, is_afk_)
            {

            }
        };
    } // namespace AI
} // namespace Botcraft
