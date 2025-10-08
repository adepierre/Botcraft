#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"

#include <optional>
#include <string>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class PartialResolvableProfile : public NetworkType
        {
            SERIALIZED_FIELD(Name, std::optional<std::string>);
            SERIALIZED_FIELD(Uuid, std::optional<UUID>);
            SERIALIZED_FIELD(Properties, std::vector<GameProfileProperty>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
