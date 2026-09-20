#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/PositionPathStepped.hpp"
#include "protocolCraft/Types/PositionPathLinear.hpp"


namespace ProtocolCraft
{
    class PositionPath : public NetworkType
    {
        SERIALIZED_FIELD(Value, Either<PositionPathStepped, PositionPathLinear>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
