#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundLoginDisconnectPacket : public BasePacket<ClientboundLoginDisconnectPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Login Disconnect";

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        SERIALIZED_FIELD(Reason, Chat);
#else
        SERIALIZED_FIELD(Reason, std::string);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
