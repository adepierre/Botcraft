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
            DECLARE_FIELDS_TYPES(std::optional<std::string>, std::optional<UUID>, std::vector<GameProfileProperty>);
            DECLARE_FIELDS_NAMES(Name,                       Uuid,                Properties);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Name);
            GETTER_SETTER(Uuid);
            GETTER_SETTER(Properties);
        };
    }
}
#endif
