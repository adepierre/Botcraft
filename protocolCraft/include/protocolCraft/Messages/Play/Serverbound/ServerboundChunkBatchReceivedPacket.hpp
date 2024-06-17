#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChunkBatchReceivedPacket : public BaseMessage<ServerboundChunkBatchReceivedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x08;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chunk Batch Received";

        DECLARE_FIELDS(
            (float),
            (DesiredChunksPerTick)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(DesiredChunksPerTick);
    };
} //ProtocolCraft
#endif
