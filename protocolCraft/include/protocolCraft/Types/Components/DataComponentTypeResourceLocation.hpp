#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeResourceLocation : public DataComponentType
        {
            SERIALIZED_FIELD(Identifier, ProtocolCraft::Identifier);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
