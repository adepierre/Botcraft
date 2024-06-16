#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPingConfigurationPacket : public BaseMessage<ClientboundPingConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x05;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ping (Configuration)";

        DECLARE_FIELDS(
            (int),
            (Id_)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
    };
} //ProtocolCraft
#endif
