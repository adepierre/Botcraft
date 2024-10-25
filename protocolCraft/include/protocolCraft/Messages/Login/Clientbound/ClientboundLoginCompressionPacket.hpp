#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginCompressionPacket : public BaseMessage<ClientboundLoginCompressionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Login Compression";

        SERIALIZED_FIELD(CompressionThreshold, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
