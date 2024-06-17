#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class KnownPack : public NetworkType
    {
        DECLARE_FIELDS(
            (std::string, std::string, std::string),
            (Namespace, Id, Version)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Namespace);
        GETTER_SETTER(Id);
        GETTER_SETTER(Version);
    };
}
#endif
