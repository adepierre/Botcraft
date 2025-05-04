#if PROTOCOL_VERSION < 755 /* < 1.17 */ || PROTOCOL_VERSION > 755 /* > 1.17 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveEntitiesPacket : public BasePacket<ClientboundRemoveEntitiesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Remove Entities";

        SERIALIZED_FIELD(EntityIds, std::vector<VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
