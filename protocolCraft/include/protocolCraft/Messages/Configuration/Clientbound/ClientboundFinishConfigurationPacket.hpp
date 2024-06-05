#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundFinishConfigurationPacket : public BaseMessage<ClientboundFinishConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x03;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Finish Configuration";

        DECLARE_EMPTY;
    };
} //ProtocolCraft
#endif
