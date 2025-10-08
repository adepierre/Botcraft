#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"

#include "protocolCraft/Types/Debug/Subtypes/Path.hpp"

namespace ProtocolCraft
{
    class DebugSubscriptionDataPathInfo : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(Path, ProtocolCraft::Path);
        SERIALIZED_FIELD(MaxNodeDistance, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
