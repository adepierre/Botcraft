#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundAcceptTeleportationPacket : public BaseMessage<ServerboundAcceptTeleportationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Accept Teleportation";

        SERIALIZED_FIELD(Id_, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
