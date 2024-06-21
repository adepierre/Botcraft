#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderSizePacket : public BaseMessage<ClientboundSetBorderSizePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Border Size";

        DECLARE_FIELDS(
            (double),
            (Size)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Size);
    };
} //ProtocolCraft
#endif
