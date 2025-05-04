#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once
#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundChunkBatchFinishedPacket : public BasePacket<ClientboundChunkBatchFinishedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chunk Batch Finished";

        SERIALIZED_FIELD(BatchSize, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
