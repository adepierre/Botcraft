#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeInteger : public DataComponentType
        {
            DECLARE_FIELDS(
                (VarInt),
                (Value)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Value);
        };
    }
}
#endif
