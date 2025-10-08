#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Debug/DebugSubscription.hpp"

namespace ProtocolCraft
{
    class ClientboundDebugEntityValuePacket : public BasePacket<ClientboundDebugEntityValuePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Debug Entity Value";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Update, DebugSubscriptionUpdate);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
