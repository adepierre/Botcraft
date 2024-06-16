#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyRange : public BrigadierProperty
    {
        DECLARE_FIELDS(
            (bool),
            (Decimals)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Decimals);
    };
}
#endif
