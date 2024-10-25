#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundSeenAdvancementsPacket : public BaseMessage<ServerboundSeenAdvancementsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Seen Advancement";

        DEFINE_CONDITION(HasTab, GetAction() == 0);

        SERIALIZED_FIELD(Action, VarInt);
        SERIALIZED_FIELD(Tab, Internal::Conditioned<Identifier, &THIS::HasTab>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
