#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeCustomModelData : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(VarInt);
            DECLARE_FIELDS_NAMES(Value);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Value);
        };
    }
}
#endif
