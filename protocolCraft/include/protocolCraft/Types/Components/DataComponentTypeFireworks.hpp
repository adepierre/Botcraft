#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFireworkExplosion.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeFireworks : public DataComponentType
        {
            SERIALIZED_FIELD(FlightDuration, VarInt);
            SERIALIZED_FIELD(Explosions, std::vector<DataComponentTypeFireworkExplosion>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
