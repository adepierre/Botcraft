#if PROTOCOL_VERSION > 493 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockBreakAckPacket : public BasePacket<ClientboundBlockBreakAckPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Block Break Ack";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(State, VarInt);
        SERIALIZED_FIELD(Action, VarInt);
        SERIALIZED_FIELD(AllGood, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

#endif
