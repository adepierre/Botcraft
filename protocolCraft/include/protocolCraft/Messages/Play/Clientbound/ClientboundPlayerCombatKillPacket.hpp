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

#if PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS(
            (VarInt,   int,      Chat),
            (PlayerId, KillerId, Message)
        );
#else
        DECLARE_FIELDS(
            (VarInt,   Chat),
            (PlayerId, Message)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(PlayerId);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        GETTER_SETTER(KillerId);
#endif
        GETTER_SETTER(Message);
    };
} //ProtocolCraft
#endif
