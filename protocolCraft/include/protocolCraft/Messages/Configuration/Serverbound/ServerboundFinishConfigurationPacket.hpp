#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundFinishConfigurationPacket : public BaseMessage<ServerboundFinishConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Finish Configuration";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
