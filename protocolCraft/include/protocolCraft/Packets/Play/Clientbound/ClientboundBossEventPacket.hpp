#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundBossEventPacket : public BasePacket<ClientboundBossEventPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Boss Event";

        DEFINE_CONDITION(Op02, GetOperation() == 0 || GetOperation() == 2);
        DEFINE_CONDITION(Op03, GetOperation() == 0 || GetOperation() == 3);
        DEFINE_CONDITION(Op04, GetOperation() == 0 || GetOperation() == 4);
        DEFINE_CONDITION(Op05, GetOperation() == 0 || GetOperation() == 5);

        SERIALIZED_FIELD(Id_, UUID);
        SERIALIZED_FIELD(Operation, VarInt);
        SERIALIZED_FIELD(Name_, Internal::Conditioned<Chat, &THIS::Op03>);
        SERIALIZED_FIELD(Pct, Internal::Conditioned<float, &THIS::Op02>);
        SERIALIZED_FIELD(Color, Internal::Conditioned<VarInt, &THIS::Op04>);
        SERIALIZED_FIELD(Overlay, Internal::Conditioned<VarInt, &THIS::Op04>);
        SERIALIZED_FIELD(Flags, Internal::Conditioned<unsigned char, &THIS::Op05>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
