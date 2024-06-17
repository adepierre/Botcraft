#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"

#include <string>

namespace ProtocolCraft
{
    class GameProfile : public NetworkType
    {
        DECLARE_FIELDS(
            (UUID, std::string, std::vector<GameProfileProperty>),
            (Uuid, Name,        Properties)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
        GETTER_SETTER(Name);
        GETTER_SETTER(Properties);
    };
} // ProtocolCraft
#endif
