#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPongConfigurationPacket : public BaseMessage<ServerboundPongConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Pong (Configuration)";

        SERIALIZED_FIELD(Id_, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
