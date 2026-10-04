#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/Types/PositionPath/PositionPathData.hpp"

#include <array>

namespace ProtocolCraft
{
    class PositionPathLinear : public PositionPathData
    {
        SERIALIZED_FIELD(EndPosition, std::array<double, 3>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
