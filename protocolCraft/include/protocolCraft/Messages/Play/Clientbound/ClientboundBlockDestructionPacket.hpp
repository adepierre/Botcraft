#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockDestructionPacket : public BaseMessage<ClientboundBlockDestructionPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Block Break Animation";

        DECLARE_FIELDS(
            (VarInt, NetworkPosition, char),
            (Id_,    Pos,             Progress)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Pos);
        GETTER_SETTER(Progress);
    };
} //ProtocolCraft
