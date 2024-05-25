#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class BlockEntityTag : public NetworkType
    {
        DECLARE_FIELDS_TYPES(Identifier, std::vector<VarInt>);
        DECLARE_FIELDS_NAMES(TagName,    Entries);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(TagName);
        GETTER_SETTER(Entries);
    };
} // ProtocolCraft
#endif
