#if PROTOCOL_VERSION < 461 /* < 1.14 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundUseBedPacket : public BaseMessage<ClientboundUseBedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x33;
#else
#error "Protocol version not implemented"
#endif

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
