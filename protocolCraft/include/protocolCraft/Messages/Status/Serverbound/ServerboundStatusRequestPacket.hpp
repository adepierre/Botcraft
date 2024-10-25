#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundStatusRequestPacket : public BaseMessage<ServerboundStatusRequestPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Status Request";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
