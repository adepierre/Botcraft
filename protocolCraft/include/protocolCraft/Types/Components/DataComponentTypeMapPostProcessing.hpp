#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeMapPostProcessing : public DataComponentType
        {
            SERIALIZED_FIELD(MapPostProcessingId, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
