#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/ChunkPos.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundForgetLevelChunkPacket : public BasePacket<ClientboundForgetLevelChunkPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Forget Level Chunk";

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Z, int);
#else
        SERIALIZED_FIELD(Pos, ChunkPos);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
