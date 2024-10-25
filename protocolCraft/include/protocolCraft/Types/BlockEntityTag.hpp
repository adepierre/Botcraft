#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class BlockEntityTag : public NetworkType
    {
        SERIALIZED_FIELD(TagName, Identifier);
        SERIALIZED_FIELD(Entries, std::vector<VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
