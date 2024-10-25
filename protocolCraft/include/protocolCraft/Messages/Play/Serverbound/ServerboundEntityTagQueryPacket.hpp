#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundEntityTagQueryPacket : public BaseMessage<ServerboundEntityTagQueryPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Entity Tag Query";

        SERIALIZED_FIELD(TransactionId, VarInt);
        SERIALIZED_FIELD(EntityId, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
