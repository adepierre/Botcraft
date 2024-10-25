#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCarriedItemPacket : public BaseMessage<ServerboundSetCarriedItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Carried Item";

        SERIALIZED_FIELD(Slot, short);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
