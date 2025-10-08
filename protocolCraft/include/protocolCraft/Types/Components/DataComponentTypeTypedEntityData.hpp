#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeTypedEntityData : public DataComponentType
        {
            SERIALIZED_FIELD(Type, VarInt);
            SERIALIZED_FIELD(Tag, NBT::UnnamedValue);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
