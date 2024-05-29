#pragma once

#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyTime : public BrigadierProperty
    {
        DECLARE_FIELDS_TYPES(int);
        DECLARE_FIELDS_NAMES(Min);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Min);
    };
}
#endif
