#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCarriedItemPacket : public BaseMessage<ServerboundSetCarriedItemPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Carried Item";

        DECLARE_FIELDS(
            (short),
            (Slot)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Slot);
    };
} //ProtocolCraft
