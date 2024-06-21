#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundTeleportToEntityPacket : public BaseMessage<ServerboundTeleportToEntityPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Teleport To Entity";

        DECLARE_FIELDS(
            (UUID),
            (Uuid)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
    };
} //ProtocolCraft
