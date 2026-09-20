#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/PositionStep.hpp"

#include <array>

namespace ProtocolCraft
{
    class PositionPathStepped : public NetworkType
    {
        SERIALIZED_FIELD(Steps, std::vector<PositionStep>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
