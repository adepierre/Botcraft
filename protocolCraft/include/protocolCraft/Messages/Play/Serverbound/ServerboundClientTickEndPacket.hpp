#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundClientTickEndPacket : public BaseMessage<ServerboundClientTickEndPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Client Tick End";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
