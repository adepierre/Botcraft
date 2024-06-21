#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPaddleBoatPacket : public BaseMessage<ServerboundPaddleBoatPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Paddle Boat";

        DECLARE_FIELDS(
            (bool, bool),
            (Left, Right)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Left);
        GETTER_SETTER(Right);
    };
} //ProtocolCraft
