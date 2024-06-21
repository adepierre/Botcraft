#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChunkBatchFinishedPacket : public BaseMessage<ClientboundChunkBatchFinishedPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Chunk Batch Finished";

        DECLARE_FIELDS(
            (VarInt),
            (BatchSize)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(BatchSize);
    };
} //ProtocolCraft
#endif
