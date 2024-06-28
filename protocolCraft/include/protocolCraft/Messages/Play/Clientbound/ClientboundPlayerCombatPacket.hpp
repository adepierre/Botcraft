#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatPacket : public BaseMessage<ClientboundPlayerCombatPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Combat";

        DECLARE_CONDITION(Event1, GetEvent() == 1);
        DECLARE_CONDITION(Event12, GetEvent() == 1 || GetEvent() == 2);
        DECLARE_CONDITION(Event2, GetEvent() == 2);

        DECLARE_FIELDS(
            (VarInt, Internal::Conditioned<VarInt, &THIS::Event1>, Internal::Conditioned<VarInt, &THIS::Event2>, Internal::Conditioned<int, &THIS::Event12>, Internal::Conditioned<Chat, &THIS::Event2>),
            (Event,  Duration,                                     PlayerId,                                     KillerId,                                   Message)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Event);
        GETTER_SETTER(Duration);
        GETTER_SETTER(KillerId);
        GETTER_SETTER(PlayerId);
        GETTER_SETTER(Message);
    };
} //ProtocolCraft
#endif
