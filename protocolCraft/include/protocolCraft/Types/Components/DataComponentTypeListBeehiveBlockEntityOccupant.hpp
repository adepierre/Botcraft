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
            DECLARE_FIELDS_TYPES(DataComponentTypeCustomData, VarInt,      VarInt);
            DECLARE_FIELDS_NAMES(EntityData,                  TicksInHive, MinTicksInHive);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(EntityData);
            GETTER_SETTER(TicksInHive);
            GETTER_SETTER(MinTicksInHive);
        };
    }
}
#endif
