#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChunkBatchReceivedPacket : public BaseMessage<ServerboundChunkBatchReceivedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chunk Batch Received";

        SERIALIZED_FIELD(DesiredChunksPerTick, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
