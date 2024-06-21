#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCookieRequestPacket : public BaseMessage<ClientboundCookieRequestPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Cookie Request";

        DECLARE_FIELDS(
            (Identifier),
            (Key)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Key);
    };
}
#endif
