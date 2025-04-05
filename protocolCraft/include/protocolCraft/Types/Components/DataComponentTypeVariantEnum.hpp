#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeVariantEnum: public DataComponentType
        {
            SERIALIZED_FIELD(Variant, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
