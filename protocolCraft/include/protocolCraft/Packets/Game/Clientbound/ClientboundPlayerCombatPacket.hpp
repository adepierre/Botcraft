#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

#if PROTOCOL_VERSION < 107 /* < 1.9 */
#include <string>
#endif

namespace ProtocolCraft
{
    class ClientboundPlayerCombatPacket : public BasePacket<ClientboundPlayerCombatPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Combat";

        DEFINE_CONDITION(Event1, GetEvent() == 1);
        DEFINE_CONDITION(Event12, GetEvent() == 1 || GetEvent() == 2);
        DEFINE_CONDITION(Event2, GetEvent() == 2);

        SERIALIZED_FIELD(Event, VarInt);
        SERIALIZED_FIELD(Duration, Internal::Conditioned<VarInt, &THIS::Event1>);
        SERIALIZED_FIELD(PlayerId, Internal::Conditioned<VarInt, &THIS::Event2>);
        SERIALIZED_FIELD(KillerId, Internal::Conditioned<int, &THIS::Event12>);
#if PROTOCOL_VERSION < 107 /* < 1.9 */
        SERIALIZED_FIELD(Message, Internal::Conditioned<std::string, &THIS::Event2>);
#else
        SERIALIZED_FIELD(Message, Internal::Conditioned<Chat, &THIS::Event2>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
