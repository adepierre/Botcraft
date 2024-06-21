#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundClientCommandPacket : public BaseMessage<ServerboundClientCommandPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Client Command";

        DECLARE_FIELDS(
            (VarInt),
            (Action)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Action);
    };
} //ProtocolCraft
