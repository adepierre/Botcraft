#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeDefault : public DataComponentType
        {
            SERIALIZED_FIELD(Tag, NBT::UnnamedValue);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
