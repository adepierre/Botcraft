#if PROTOCOL_VERSION > 493 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockBreakAckPacket : public BaseMessage<ClientboundBlockBreakAckPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Block Break Ack";

        DECLARE_FIELDS(
            (NetworkPosition, VarInt, VarInt, bool),
            (Pos,             State,  Action, AllGood)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(State);
        GETTER_SETTER(Action);
        GETTER_SETTER(AllGood);
    };
} //ProtocolCraft

#endif
