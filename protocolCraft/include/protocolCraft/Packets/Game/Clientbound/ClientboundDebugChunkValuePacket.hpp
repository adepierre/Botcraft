#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/ChunkPos.hpp"
#include "protocolCraft/Types/Debug/DebugSubscription.hpp"

namespace ProtocolCraft
{
    class ClientboundDebugChunkValuePacket : public BasePacket<ClientboundDebugChunkValuePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Debug Chunk Value";

        SERIALIZED_FIELD(ChunkPos, ProtocolCraft::ChunkPos);
        SERIALIZED_FIELD(Update, DebugSubscriptionUpdate);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
