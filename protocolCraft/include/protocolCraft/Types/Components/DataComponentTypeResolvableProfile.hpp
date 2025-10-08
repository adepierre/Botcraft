#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"

#include <optional>
#include <string>
#include <vector>
#else
#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/GameProfile/GameProfile.hpp"
#include "protocolCraft/Types/Components/Subtypes/PartialResolvableProfile.hpp"
#include "protocolCraft/Types/Components/Subtypes/PlayerSkinPatch.hpp"
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeResolvableProfile : public DataComponentType
        {
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
            SERIALIZED_FIELD(Name, std::optional<std::string>);
            SERIALIZED_FIELD(Uuid, std::optional<UUID>);
            SERIALIZED_FIELD(Properties, std::vector<GameProfileProperty>);
#else
            SERIALIZED_FIELD(Unpack, Either<GameProfile, PartialResolvableProfile>);
            SERIALIZED_FIELD(SkinPatch, PlayerSkinPatch);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
