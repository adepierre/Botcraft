#pragma once

#include "botcraft/Game/BaseClient.hpp"
#include "botcraft/AI/Blackboard.hpp"

namespace Botcraft
{
    namespace AI
    {
        /// <summary>
        /// A base class for any client using the advanced behaviour stuff.
        /// Extends the base client with blackboard that can store any kind of data.
        /// You should *not* inherit from this class, but from BaseBehaviourClient
        /// instead.
        /// </summary>
        class BehaviourClient : public BaseClient
        {
        public:
            BehaviourClient(const bool use_renderer_, const bool afk_only_ = false);
            virtual ~BehaviourClient();

            virtual void Yield() = 0;

            Blackboard& GetBlackboard();
            void RemoveBlackboardEntries(const std::vector<std::string>& entries);

        protected:
            Blackboard blackboard;
        };
    } // namespace AI
} // namespace Botcraft
