#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundTeleportToEntityPacket : public BasePacket<ServerboundTeleportToEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Teleport To Entity";

        SERIALIZED_FIELD(Uuid, UUID);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
