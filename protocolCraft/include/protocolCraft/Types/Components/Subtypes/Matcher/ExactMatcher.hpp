#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

#include <string>

namespace ProtocolCraft
{
    namespace Components
    {
        class ExactMatcher : public NetworkType
        {
            DECLARE_FIELDS(
                (std::string),
                (Value)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Value);
        };
    }
}
#endif
