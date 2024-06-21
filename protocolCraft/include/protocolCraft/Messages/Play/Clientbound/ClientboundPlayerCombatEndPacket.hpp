#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatEndPacket : public BaseMessage<ClientboundPlayerCombatEndPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Combat End";

#if PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS(
            (VarInt,   int),
            (Duration, KillerId)
        );
#else
        DECLARE_FIELDS(
            (VarInt),
            (Duration)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Duration);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        GETTER_SETTER(KillerId);
#endif
    };
} //ProtocolCraft
#endif
