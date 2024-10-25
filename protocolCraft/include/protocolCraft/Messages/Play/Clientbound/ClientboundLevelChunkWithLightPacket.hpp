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

        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Z, int);
        SERIALIZED_FIELD(ChunkData, ClientboundLevelChunkPacketData);
        SERIALIZED_FIELD(LightData, ClientboundLightUpdatePacketData);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
