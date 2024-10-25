#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyString : public BrigadierProperty
    {
        SERIALIZED_FIELD(ReadType, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
