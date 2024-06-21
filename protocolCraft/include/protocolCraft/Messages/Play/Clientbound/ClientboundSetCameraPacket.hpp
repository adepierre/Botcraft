#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetCameraPacket : public BaseMessage<ClientboundSetCameraPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Camera";

        DECLARE_FIELDS(
            (VarInt),
            (CameraId)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(CameraId);
    };
} //ProtocolCraft
