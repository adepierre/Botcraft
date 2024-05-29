#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeMapPostProcessing : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(VarInt);
            DECLARE_FIELDS_NAMES(MapPostProcessingId);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(MapPostProcessingId);
        };
    }
}
#endif
