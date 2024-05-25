#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/ChunkPos.hpp"

namespace ProtocolCraft
{
    class ChunkBiomeData : public NetworkType
    {
        DECLARE_FIELDS_TYPES(ChunkPos, std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(Pos,      Buffer);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(Buffer);
    };
}
#endif
