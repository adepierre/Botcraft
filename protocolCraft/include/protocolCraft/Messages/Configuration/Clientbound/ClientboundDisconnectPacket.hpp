#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundDisconnectConfigurationPacket : public BaseMessage<ClientboundDisconnectConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Disconnect (Configuration)";

        SERIALIZED_FIELD(Reason, Chat);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
