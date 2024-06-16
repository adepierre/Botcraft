#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCookieRequestPacket : public BaseMessage<ClientboundCookieRequestPacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x16;
#else
#error "Protocol version not implemented"
#endif
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
