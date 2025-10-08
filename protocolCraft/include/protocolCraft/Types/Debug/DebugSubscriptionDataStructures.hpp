#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"
#include "protocolCraft/Types/Debug/Subtypes/DebugStructureInfo.hpp"

namespace ProtocolCraft
{
    class DebugSubscriptionDataStructures : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(Structures, std::vector<DebugStructureInfo>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
