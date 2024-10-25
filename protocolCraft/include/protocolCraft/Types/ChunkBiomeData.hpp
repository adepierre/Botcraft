#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/ChunkPos.hpp"

namespace ProtocolCraft
{
    class ChunkBiomeData : public NetworkType
    {
        SERIALIZED_FIELD(Pos, ChunkPos);
        SERIALIZED_FIELD(Buffer, std::vector<unsigned char>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
