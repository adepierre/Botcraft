#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyTime : public BrigadierProperty
    {
        SERIALIZED_FIELD(Min, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
