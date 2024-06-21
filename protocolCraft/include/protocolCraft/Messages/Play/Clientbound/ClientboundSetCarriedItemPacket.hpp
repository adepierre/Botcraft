#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetCarriedItemPacket : public BaseMessage<ClientboundSetCarriedItemPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Carried Item";

        DECLARE_FIELDS(
            (char),
            (Slot)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Slot);
    };
}
