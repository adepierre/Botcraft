#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacket : public BaseMessage<ClientboundMoveEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Move Entity";

        SERIALIZED_FIELD(EntityId, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
