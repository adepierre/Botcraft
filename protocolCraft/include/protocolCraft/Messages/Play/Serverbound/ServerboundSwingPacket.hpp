#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSwingPacket : public BaseMessage<ServerboundSwingPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Swing";

        DECLARE_FIELDS(
            (VarInt),
            (Hand)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Hand);
    };
} //ProtocolCraft
