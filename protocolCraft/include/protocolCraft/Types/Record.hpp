#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Record : public NetworkType
    {
        DECLARE_FIELDS(
            (unsigned char, unsigned char, VarInt),
            (HorizontalPosition, YCoordinate, BlockId)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(HorizontalPosition);
        GETTER_SETTER(YCoordinate);
        GETTER_SETTER(BlockId);
    };
}
#endif
