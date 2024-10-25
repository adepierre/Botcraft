#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class BlockPositionSource : public PositionSource
    {
        SERIALIZED_FIELD(Pos, NetworkPosition);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
