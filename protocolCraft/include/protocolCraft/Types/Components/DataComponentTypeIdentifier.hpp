#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeIdentifier : public DataComponentType
        {
            SERIALIZED_FIELD(Identifier, ProtocolCraft::Identifier);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
