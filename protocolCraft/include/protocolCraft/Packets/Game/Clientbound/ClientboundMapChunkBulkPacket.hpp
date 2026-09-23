#if PROTOCOL_VERSION < 107 /* < 1.9 */
#pragma once
#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundMapChunkBulkPacket : public BasePacket<ClientboundMapChunkBulkPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Map Chunk Bulk";

        SERIALIZED_FIELD(IsOverworld, bool);
        SERIALIZED_FIELD(ChunkCount, VarInt);
        SERIALIZED_FIELD(ChunksData, Internal::Vector<unsigned char, void, 0>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
