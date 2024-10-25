#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundStoreCookieConfigurationPacket : public BaseMessage<ClientboundStoreCookieConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Store Cookie (Configuration)";

        SERIALIZED_FIELD(Key, Identifier);
        SERIALIZED_FIELD(Payload, Internal::Vector<unsigned char, void, 0>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
