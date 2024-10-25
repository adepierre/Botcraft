#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerInfoRemovePacket : public BaseMessage<ClientboundPlayerInfoRemovePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Info Remove";

        SERIALIZED_FIELD(ProfileIds, std::vector<UUID>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
