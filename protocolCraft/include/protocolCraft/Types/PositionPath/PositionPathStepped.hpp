#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/Types/PositionPath/PositionPathData.hpp"
#include "protocolCraft/Types/PositionStep.hpp"

#include <vector>

namespace ProtocolCraft
{
    class PositionPathStepped : public PositionPathData
    {
        SERIALIZED_FIELD(Steps, std::vector<PositionStep>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
