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
            SERIALIZED_FIELD(Value, std::string);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
