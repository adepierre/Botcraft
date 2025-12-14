#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeEitherRegistryVarint : public DataComponentType
        {
            SERIALIZED_FIELD(Value, Either<VarInt, Identifier>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
