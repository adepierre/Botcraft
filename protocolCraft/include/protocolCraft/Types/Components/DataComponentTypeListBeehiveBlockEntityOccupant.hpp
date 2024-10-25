#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCustomData.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeListBeehiveBlockEntityOccupant : public DataComponentType
        {
            SERIALIZED_FIELD(EntityData, DataComponentTypeCustomData);
            SERIALIZED_FIELD(TicksInHive, VarInt);
            SERIALIZED_FIELD(MinTicksInHive, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
