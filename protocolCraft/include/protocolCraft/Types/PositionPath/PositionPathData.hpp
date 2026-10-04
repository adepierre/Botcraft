#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class PositionPathData : public NetworkType
    {
    public:
        virtual ~PositionPathData() override {}
    };
} // ProtocolCraft
#endif
