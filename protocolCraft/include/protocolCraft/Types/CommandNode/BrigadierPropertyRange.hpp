#if PROTOCOL_VERSION > 344 /* > 1.12.2 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyRange : public BrigadierProperty
    {
        SERIALIZED_FIELD(Decimals, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
