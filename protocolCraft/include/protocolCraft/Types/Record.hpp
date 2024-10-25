#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Record : public NetworkType
    {
        SERIALIZED_FIELD(HorizontalPosition, unsigned char);
        SERIALIZED_FIELD(YCoordinate, unsigned char);
        SERIALIZED_FIELD(BlockId, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
