#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class SuspiciousStewEntry : public NetworkType
        {
            DECLARE_FIELDS(
                (VarInt, VarInt),
                (Effect, Duration)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Effect);
            GETTER_SETTER(Duration);
        };
    }
}
#endif
