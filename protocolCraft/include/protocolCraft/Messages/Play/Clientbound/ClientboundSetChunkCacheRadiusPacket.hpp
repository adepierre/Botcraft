#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetChunkCacheRadiusPacket : public BaseMessage<ClientboundSetChunkCacheRadiusPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Chunk Cache Radius";

        DECLARE_FIELDS(
            (VarInt),
            (Radius)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Radius);
    };
} //ProtocolCraft
#endif
