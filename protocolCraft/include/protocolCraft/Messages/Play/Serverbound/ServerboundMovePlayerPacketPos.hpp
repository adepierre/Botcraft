#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketPos : public BaseMessage<ServerboundMovePlayerPacketPos>
    {
    public:

        static constexpr std::string_view packet_name = "Move Player Pos";

        DECLARE_FIELDS(
            (double, double, double, bool),
            (X,      Y,      Z,      OnGround)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(OnGround);
    };
} //ProtocolCraft
