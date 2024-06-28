#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundSeenAdvancementsPacket : public BaseMessage<ServerboundSeenAdvancementsPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Seen Advancement";

        DECLARE_CONDITION(HasTab, GetAction() == 0);

        DECLARE_FIELDS(
            (VarInt, Internal::Conditioned<Identifier, &ServerboundSeenAdvancementsPacket::HasTab>),
            (Action, Tab)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Action);
        GETTER_SETTER(Tab);
    };
} //ProtocolCraft
