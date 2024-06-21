#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPongPacket : public BaseMessage<ServerboundPongPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Pong";

        DECLARE_FIELDS(
            (int),
            (Id_)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
    };
} //ProtocolCraft
#endif
