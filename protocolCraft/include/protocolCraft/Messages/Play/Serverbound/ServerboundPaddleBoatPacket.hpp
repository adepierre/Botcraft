#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPaddleBoatPacket : public BaseMessage<ServerboundPaddleBoatPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Paddle Boat";

        SERIALIZED_FIELD(Left, bool);
        SERIALIZED_FIELD(Right, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
