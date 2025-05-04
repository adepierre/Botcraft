#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatEnterPacket : public BasePacket<ClientboundPlayerCombatEnterPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Combat Enter";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
