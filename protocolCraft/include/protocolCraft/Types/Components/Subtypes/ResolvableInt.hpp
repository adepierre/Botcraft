#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class ResolvableInt : public NetworkType
        {
            SERIALIZED_FIELD(Value, Either<int, Identifier>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
