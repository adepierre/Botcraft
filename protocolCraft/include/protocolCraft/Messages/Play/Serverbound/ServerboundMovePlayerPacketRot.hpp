#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketRot : public BaseMessage<ServerboundMovePlayerPacketRot>
    {
    public:
        static constexpr std::string_view packet_name = "Move Player Rot";

        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
