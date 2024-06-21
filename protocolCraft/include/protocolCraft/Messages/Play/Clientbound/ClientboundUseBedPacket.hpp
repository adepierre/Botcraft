#if PROTOCOL_VERSION < 461 /* < 1.14 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundUseBedPacket : public BaseMessage<ClientboundUseBedPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Use Bed";

        DECLARE_FIELDS(
            (VarInt, NetworkPosition),
            (EntityId, Location)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(Location);
    };
} //ProtocolCraft
#endif
