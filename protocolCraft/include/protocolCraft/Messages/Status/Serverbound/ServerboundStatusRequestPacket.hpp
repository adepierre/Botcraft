#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundStatusRequestPacket : public BaseMessage<ServerboundStatusRequestPacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Status Request";

        DECLARE_EMPTY;

    };
} // ProtocolCraft
