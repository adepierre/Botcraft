#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeSwingAnimation : public DataComponentType
        {
            SERIALIZED_FIELD(Type, VarInt);
            SERIALIZED_FIELD(Duration, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
