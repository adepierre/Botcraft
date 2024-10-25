#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class SuspiciousStewEntry : public NetworkType
        {
            SERIALIZED_FIELD(Effect, VarInt);
            SERIALIZED_FIELD(Duration, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
