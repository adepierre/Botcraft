#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"
#include "protocolCraft/Types/Debug/Subtypes/DebugGoal.hpp"

#include <vector>

namespace ProtocolCraft
{
    class DebugSubscriptionDataGoalInfo : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(Goals, std::vector<DebugGoal>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
