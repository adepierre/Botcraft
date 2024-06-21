#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockUpdatePacket : public BaseMessage<ClientboundBlockUpdatePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Block Update";

        DECLARE_FIELDS(
            (NetworkPosition, VarInt),
            (Pos,             Blockstate)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(Blockstate);
    };
} //ProtocolCraft
