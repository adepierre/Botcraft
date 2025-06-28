#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class TrackedWaypointData : public NetworkType
    {
    public:
        virtual ~TrackedWaypointData() override {}
    };
}
#endif
