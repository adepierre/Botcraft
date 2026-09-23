#if PROTOCOL_VERSION < 107 /* < 1.9 */
#pragma once
#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayCompressionPacket : public BasePacket<ClientboundPlayCompressionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Play Compression";

        SERIALIZED_FIELD(Threshold, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
