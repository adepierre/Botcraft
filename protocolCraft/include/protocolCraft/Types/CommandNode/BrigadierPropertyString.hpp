#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyString : public BrigadierProperty
    {
        DECLARE_FIELDS_TYPES(VarInt);
        DECLARE_FIELDS_NAMES(ReadType);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ReadType);
    };
}
#endif
