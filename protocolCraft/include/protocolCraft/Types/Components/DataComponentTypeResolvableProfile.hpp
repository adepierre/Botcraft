#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"

#include <optional>
#include <string>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeResolvableProfile : public DataComponentType
        {
            SERIALIZED_FIELD(Name, std::optional<std::string>);
            SERIALIZED_FIELD(Uuid, std::optional<UUID>);
            SERIALIZED_FIELD(Properties, std::vector<GameProfileProperty>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
