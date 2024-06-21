#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockEventPacket : public BaseMessage<ClientboundBlockEventPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Block Event";

        DECLARE_FIELDS(
            (NetworkPosition, unsigned char, unsigned char, VarInt),
            (Pos,             B0,            B1,            Block)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(B0);
        GETTER_SETTER(B1);
        GETTER_SETTER(Block);
    };
} //ProtocolCraft
