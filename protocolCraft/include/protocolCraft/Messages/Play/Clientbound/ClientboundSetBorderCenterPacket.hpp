#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderCenterPacket : public BaseMessage<ClientboundSetBorderCenterPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Border Center";

        DECLARE_FIELDS(
            (double,     double),
            (NewCenterX, NewCenterZ)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(NewCenterX);
        GETTER_SETTER(NewCenterZ);
    };
} //ProtocolCraft
#endif
