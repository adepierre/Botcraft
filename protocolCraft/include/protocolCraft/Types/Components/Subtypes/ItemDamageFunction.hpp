#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class ItemDamageFunction : public NetworkType
        {
            SERIALIZED_FIELD(Threshold, float);
            SERIALIZED_FIELD(Base, float);
            SERIALIZED_FIELD(Factor, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
