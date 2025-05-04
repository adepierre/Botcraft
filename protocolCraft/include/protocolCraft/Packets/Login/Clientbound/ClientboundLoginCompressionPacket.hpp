#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginCompressionPacket : public BasePacket<ClientboundLoginCompressionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Login Compression";

        SERIALIZED_FIELD(CompressionThreshold, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
