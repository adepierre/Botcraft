#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundDisconnectConfigurationPacket : public BaseMessage<ClientboundDisconnectConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x02;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Disconnect (Configuration)";

        DECLARE_FIELDS(
            (Chat),
            (Reason)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Reason);
    };
} //ProtocolCraft
#endif
