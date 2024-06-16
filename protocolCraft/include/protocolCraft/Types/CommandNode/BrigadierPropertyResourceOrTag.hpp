#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyResourceOrTag : public BrigadierProperty
    {
        DECLARE_FIELDS(
            (Identifier),
            (Registry)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Registry);
    };
}
#endif
