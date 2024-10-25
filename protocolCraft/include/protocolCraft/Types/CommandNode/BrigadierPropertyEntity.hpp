#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyEntity : public BrigadierProperty
    {
        SERIALIZED_FIELD(Flags, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
