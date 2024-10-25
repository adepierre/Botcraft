#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatKillPacket : public BaseMessage<ClientboundPlayerCombatKillPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Combat Kill";

        SERIALIZED_FIELD(PlayerId, VarInt);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        SERIALIZED_FIELD(KillerId, int);
#endif
        SERIALIZED_FIELD(Message, Chat);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
