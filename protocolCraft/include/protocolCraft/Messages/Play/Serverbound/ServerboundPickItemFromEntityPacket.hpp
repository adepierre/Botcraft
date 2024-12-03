#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPickItemFromEntityPacket : public BaseMessage<ServerboundPickItemFromEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Pick Item From Entity";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(IncludeData, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
