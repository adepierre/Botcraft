#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/BeehiveBlockEntityOccupant.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeListBeehiveBlockEntityOccupant : public DataComponentType
        {
            SERIALIZED_FIELD(Bees, std::vector<BeehiveBlockEntityOccupant>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
