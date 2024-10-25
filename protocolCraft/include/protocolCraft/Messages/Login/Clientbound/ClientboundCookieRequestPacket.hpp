#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCookieRequestLoginPacket : public BaseMessage<ClientboundCookieRequestLoginPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Cookie Request (Login)";

        SERIALIZED_FIELD(Key, Identifier);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
