#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundStatusRequestPacket : public BasePacket<ServerboundStatusRequestPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Status Request";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
