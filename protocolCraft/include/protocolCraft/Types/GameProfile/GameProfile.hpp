#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"

#include <string>

namespace ProtocolCraft
{
    class GameProfile : public NetworkType
    {
        SERIALIZED_FIELD(Uuid, UUID);
        SERIALIZED_FIELD(Name, std::string);
        SERIALIZED_FIELD(Properties, std::vector<GameProfileProperty>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
