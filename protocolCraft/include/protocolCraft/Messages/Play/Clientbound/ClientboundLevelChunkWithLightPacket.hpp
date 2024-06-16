#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/ClientboundLevelChunkPacketData.hpp"
#include "protocolCraft/Types/ClientboundLightUpdatePacketData.hpp"

namespace ProtocolCraft
{

    class ClientboundLevelChunkWithLightPacket : public BaseMessage<ClientboundLevelChunkWithLightPacket>
    {
    public:
#if   PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x27;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Level Chunk With Light";

        DECLARE_FIELDS(
            (int, int, ClientboundLevelChunkPacketData, ClientboundLightUpdatePacketData),
            (X,   Z,   ChunkData,                       LightData)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Z);
        GETTER_SETTER(ChunkData);
        GETTER_SETTER(LightData);
    };
} //ProtocolCraft
#endif
