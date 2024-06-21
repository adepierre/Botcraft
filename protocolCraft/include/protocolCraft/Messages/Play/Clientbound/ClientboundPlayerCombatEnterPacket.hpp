#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatEnterPacket : public BaseMessage<ClientboundPlayerCombatEnterPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Combat Enter";

        DECLARE_EMPTY;
    };
} //ProtocolCraft
#endif
