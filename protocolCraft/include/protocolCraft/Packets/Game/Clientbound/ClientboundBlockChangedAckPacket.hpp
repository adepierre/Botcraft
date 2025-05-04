#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockChangedAckPacket : public BasePacket<ClientboundBlockChangedAckPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Block Changed Ack";

        SERIALIZED_FIELD(Sequence, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

#endif
