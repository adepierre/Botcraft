#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/ChunkBiomeData.hpp"

namespace ProtocolCraft
{
    class ClientboundChunksBiomesPacket : public BaseMessage<ClientboundChunksBiomesPacket>
    {
    public:
#if   PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x0E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chunks Biome";

        DECLARE_FIELDS_TYPES(std::vector<ChunkBiomeData>);
        DECLARE_FIELDS_NAMES(ChunkBiomeData);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ChunkBiomeData);
    };
} //ProtocolCraft
#endif
