#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeRarity : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(VarInt);
            DECLARE_FIELDS_NAMES(RarityId);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(RarityId);
        };
    }
}
#endif
