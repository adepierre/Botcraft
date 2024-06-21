#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCookieRequestConfigurationPacket : public BaseMessage<ClientboundCookieRequestConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Cookie Request (Configuration)";

        DECLARE_FIELDS(
            (Identifier),
            (Key)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Key);
    };
}
#endif
