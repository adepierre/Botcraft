#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketPos : public BaseMessage<ServerboundMovePlayerPacketPos>
    {
    public:
        static constexpr std::string_view packet_name = "Move Player Pos";

        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
