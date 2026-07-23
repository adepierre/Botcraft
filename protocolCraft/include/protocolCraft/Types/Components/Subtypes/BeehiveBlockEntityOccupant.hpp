#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
#include "protocolCraft/Types/Components/DataComponentTypeCustomData.hpp"
#else
#include "protocolCraft/Types/Components/DataComponentTypeTypedEntityData.hpp"
#endif


namespace ProtocolCraft
{
    namespace Components
    {
        class BeehiveBlockEntityOccupant : public NetworkType
        {
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
            SERIALIZED_FIELD(EntityData, DataComponentTypeCustomData);
#else
            SERIALIZED_FIELD(EntityData, DataComponentTypeTypedEntityData);
#endif
            SERIALIZED_FIELD(TicksInHive, VarInt);
            SERIALIZED_FIELD(MinTicksInHive, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
