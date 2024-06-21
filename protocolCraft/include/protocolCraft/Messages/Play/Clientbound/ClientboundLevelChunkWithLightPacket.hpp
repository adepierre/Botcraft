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
