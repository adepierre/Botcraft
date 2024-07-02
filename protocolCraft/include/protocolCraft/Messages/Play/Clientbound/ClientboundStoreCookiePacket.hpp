#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundStoreCookiePacket : public BaseMessage<ClientboundStoreCookiePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Store Cookie";

        DECLARE_FIELDS(
            (Identifier, Internal::Vector<unsigned char, void, 0>),
            (Key,        Payload)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Key);
        GETTER_SETTER(Payload);
    };
}
#endif
