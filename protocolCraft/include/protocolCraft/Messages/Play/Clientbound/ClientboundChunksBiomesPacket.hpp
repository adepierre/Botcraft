#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/ChunkBiomeData.hpp"

namespace ProtocolCraft
{
    class ClientboundChunksBiomesPacket : public BaseMessage<ClientboundChunksBiomesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Chunks Biome";

        DECLARE_FIELDS(
            (std::vector<ChunkBiomeData>),
            (ChunkBiomeData)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ChunkBiomeData);
    };
} //ProtocolCraft
#endif
