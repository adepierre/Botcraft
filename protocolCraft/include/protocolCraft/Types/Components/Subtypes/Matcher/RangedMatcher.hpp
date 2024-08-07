#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class RangedMatcher : public NetworkType
        {
            DECLARE_FIELDS(
                (std::optional<std::string>, std::optional<std::string>),
                (MinValue,                   MaxValue)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(MinValue);
            GETTER_SETTER(MaxValue);

        };
    }
}
#endif
