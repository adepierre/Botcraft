#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundBossEventPacket : public BaseMessage<ClientboundBossEventPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Boss Event";

        DECLARE_CONDITION(Op02, GetOperation() == 0 || GetOperation() == 2);
        DECLARE_CONDITION(Op03, GetOperation() == 0 || GetOperation() == 3);
        DECLARE_CONDITION(Op04, GetOperation() == 0 || GetOperation() == 4);
        DECLARE_CONDITION(Op05, GetOperation() == 0 || GetOperation() == 5);

        DECLARE_FIELDS(
            (UUID, VarInt,    Internal::Conditioned<Chat, &THIS::Op03>, Internal::Conditioned<float, &THIS::Op02>, Internal::Conditioned<VarInt, &THIS::Op04>, Internal::Conditioned<VarInt, &THIS::Op04>, Internal::Conditioned<unsigned char, &THIS::Op05>),
            (Id_,  Operation, Name_,                                    Pct,                                       Color,                                      Overlay,                                    Flags)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Operation);
        GETTER_SETTER(Name_);
        GETTER_SETTER(Pct);
        GETTER_SETTER(Color);
        GETTER_SETTER(Overlay);
        GETTER_SETTER(Flags);
    };
} //ProtocolCraft
