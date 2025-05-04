#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundAcceptTeleportationPacket : public BasePacket<ServerboundAcceptTeleportationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Accept Teleportation";

        SERIALIZED_FIELD(Id_, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
