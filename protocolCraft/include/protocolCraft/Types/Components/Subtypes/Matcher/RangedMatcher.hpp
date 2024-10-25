#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class RangedMatcher : public NetworkType
        {
            SERIALIZED_FIELD(MinValue, std::optional<std::string>);
            SERIALIZED_FIELD(MaxValue, std::optional<std::string>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
