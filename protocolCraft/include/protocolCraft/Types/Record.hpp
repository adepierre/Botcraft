#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Record : public NetworkType
    {
        DECLARE_FIELDS_TYPES(unsigned char, unsigned char, VarInt);
        DECLARE_FIELDS_NAMES(HorizontalPosition, YCoordinate, BlockId);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(HorizontalPosition);
        GETTER_SETTER(YCoordinate);
        GETTER_SETTER(BlockId);
    };
}
#endif
