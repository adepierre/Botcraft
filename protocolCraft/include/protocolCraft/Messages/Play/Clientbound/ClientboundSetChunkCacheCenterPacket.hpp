#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetChunkCacheCenterPacket : public BaseMessage<ClientboundSetChunkCacheCenterPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Chunk Cache Center";

        DECLARE_FIELDS(
            (VarInt, VarInt),
            (X,      Z)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Z);
    };
} //ProtocolCraft
#endif
