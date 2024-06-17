#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginCompressionPacket : public BaseMessage<ClientboundLoginCompressionPacket>
    {
    public:
        static constexpr int packet_id = 0x03;
        static constexpr std::string_view packet_name = "Login Compression";

        DECLARE_FIELDS(
            (VarInt),
            (CompressionThreshold)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(CompressionThreshold);
    };
} //ProtocolCraft
