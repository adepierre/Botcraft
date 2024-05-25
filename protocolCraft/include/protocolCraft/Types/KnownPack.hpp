#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class KnownPack : public NetworkType
    {
        DECLARE_FIELDS_TYPES(std::string, std::string, std::string);
        DECLARE_FIELDS_NAMES(Namespace, Id, Version);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Namespace);
        GETTER_SETTER(Id);
        GETTER_SETTER(Version);
    };
}
#endif
