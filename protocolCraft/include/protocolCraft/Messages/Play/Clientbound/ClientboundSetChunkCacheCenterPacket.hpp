#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetChunkCacheCenterPacket : public BaseMessage<ClientboundSetChunkCacheCenterPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Chunk Cache Center";

        SERIALIZED_FIELD(X, VarInt);
        SERIALIZED_FIELD(Z, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
