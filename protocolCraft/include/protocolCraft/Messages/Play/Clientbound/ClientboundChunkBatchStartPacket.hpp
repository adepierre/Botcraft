#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChunkBatchStartPacket : public BaseMessage<ClientboundChunkBatchStartPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chunk Batch Start";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
