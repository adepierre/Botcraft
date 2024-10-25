#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyResourceOrTag : public BrigadierProperty
    {
        SERIALIZED_FIELD(Registry, Identifier);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
