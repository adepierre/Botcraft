#if PROTOCOL_VERSION < 755 /* < 1.17 */ || PROTOCOL_VERSION > 755 /* > 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveEntitiesPacket : public BaseMessage<ClientboundRemoveEntitiesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Remove Entities";

        DECLARE_FIELDS(
            (std::vector<VarInt>),
            (EntityIds)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityIds);
    };
} //ProtocolCraft
#endif
