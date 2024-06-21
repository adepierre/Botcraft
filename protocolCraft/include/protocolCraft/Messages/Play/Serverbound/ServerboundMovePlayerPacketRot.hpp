#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketRot : public BaseMessage<ServerboundMovePlayerPacketRot>
    {
    public:

        static constexpr std::string_view packet_name = "Move Player Rot";

        DECLARE_FIELDS(
            (float, float, bool),
            (YRot,  XRot,  OnGround)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
        GETTER_SETTER(OnGround);
    };
} //ProtocolCraft
