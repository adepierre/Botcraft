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

        SERIALIZED_FIELD(Key, Identifier);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
