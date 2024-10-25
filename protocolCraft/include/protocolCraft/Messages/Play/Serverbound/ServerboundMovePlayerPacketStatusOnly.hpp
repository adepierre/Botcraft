#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketStatusOnly : public BaseMessage<ServerboundMovePlayerPacketStatusOnly>
    {
    public:
        static constexpr std::string_view packet_name = "Move Player Status Only";

        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
