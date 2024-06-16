#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class BannerPatternLayer : public NetworkType
        {
            DECLARE_FIELDS(
                (VarInt, VarInt),
                (Pattern, Color)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Pattern);
            GETTER_SETTER(Color);
        };
    }
}
#endif
