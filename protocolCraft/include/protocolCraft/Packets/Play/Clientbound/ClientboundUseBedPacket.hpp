#if PROTOCOL_VERSION < 461 /* < 1.14 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundUseBedPacket : public BasePacket<ClientboundUseBedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Use Bed";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Location, NetworkPosition);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
