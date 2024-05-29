#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeResourceLocation : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(Identifier);
            DECLARE_FIELDS_NAMES(Identifier);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Identifier);
        };
    }
}
#endif
