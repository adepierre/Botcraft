#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class DebugSubscriptionData : public NetworkType
    {
    public:
        virtual ~DebugSubscriptionData() override {};
    };
}
#endif
