#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/BannerPattern.hpp"
#include "protocolCraft/Types/Holder.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class BannerPatternLayer : public NetworkType
        {
            SERIALIZED_FIELD(Pattern, Holder<BannerPattern>);
            SERIALIZED_FIELD(Color, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
