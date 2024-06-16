#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeDyeColor : public DataComponentType
        {
            DECLARE_FIELDS(
                (VarInt),
                (ColorId)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(ColorId);
        };
    }
}
#endif
