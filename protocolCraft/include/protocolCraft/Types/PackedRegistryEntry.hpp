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
        SERIALIZED_FIELD(Id, Identifier);
        SERIALIZED_FIELD(Data, std::optional<NBT::UnnamedValue>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
