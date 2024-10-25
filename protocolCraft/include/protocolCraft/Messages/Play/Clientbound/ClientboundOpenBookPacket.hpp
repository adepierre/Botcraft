#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenBookPacket : public BaseMessage<ClientboundOpenBookPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Open Book";

        SERIALIZED_FIELD(Hand, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
