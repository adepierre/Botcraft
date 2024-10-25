#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class KnownPack : public NetworkType
    {
        SERIALIZED_FIELD(Namespace, std::string);
        SERIALIZED_FIELD(Id, std::string);
        SERIALIZED_FIELD(Version, std::string);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
