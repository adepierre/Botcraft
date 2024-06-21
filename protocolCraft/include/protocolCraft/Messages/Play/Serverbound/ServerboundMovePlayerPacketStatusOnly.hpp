#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketStatusOnly : public BaseMessage<ServerboundMovePlayerPacketStatusOnly>
    {
    public:

        static constexpr std::string_view packet_name = "Move Player Status Only";

        DECLARE_FIELDS(
            (bool),
            (OnGround)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(OnGround);
    };
} //ProtocolCraft
#endif
