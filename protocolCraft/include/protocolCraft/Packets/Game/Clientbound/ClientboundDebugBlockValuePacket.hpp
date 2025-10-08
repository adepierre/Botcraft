#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/Debug/DebugSubscription.hpp"

namespace ProtocolCraft
{
    class ClientboundDebugBlockValuePacket : public BasePacket<ClientboundDebugBlockValuePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Debug Block Value";

        SERIALIZED_FIELD(BlockPos, NetworkPosition);
        SERIALIZED_FIELD(Update, DebugSubscriptionUpdate);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
