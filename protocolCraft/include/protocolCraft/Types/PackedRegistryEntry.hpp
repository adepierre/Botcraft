#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

#include <optional>

namespace ProtocolCraft
{
    class PackedRegistryEntry : public NetworkType
    {
        DECLARE_FIELDS(
            (Identifier, std::optional<NBT::UnnamedValue>),
            (Id,         Data)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id);
        GETTER_SETTER(Data);
    };
}
#endif
