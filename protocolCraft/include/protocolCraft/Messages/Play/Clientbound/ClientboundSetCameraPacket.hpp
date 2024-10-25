#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetCameraPacket : public BaseMessage<ClientboundSetCameraPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Camera";

        SERIALIZED_FIELD(CameraId, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
