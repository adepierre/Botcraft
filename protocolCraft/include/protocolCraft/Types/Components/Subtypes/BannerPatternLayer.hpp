#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class BannerPatternLayer : public NetworkType
        {
            SERIALIZED_FIELD(Pattern, VarInt);
            SERIALIZED_FIELD(Color, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
