#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundClientCommandPacket : public BaseMessage<ServerboundClientCommandPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Client Command";

        SERIALIZED_FIELD(Action, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
