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

        SERIALIZED_FIELD(Duration, VarInt);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        SERIALIZED_FIELD(KillerId, int);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
