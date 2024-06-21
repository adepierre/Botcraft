#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundLoginDisconnectPacket : public BaseMessage<ClientboundLoginDisconnectPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Login Disconnect";

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (Chat),
            (Reason)
        );
#else
        DECLARE_FIELDS(
            (std::string),
            (Reason)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Reason);
    };
}
