#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBoolean : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(bool);
            DECLARE_FIELDS_NAMES(Value);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Value);
        };
    }
}
#endif
