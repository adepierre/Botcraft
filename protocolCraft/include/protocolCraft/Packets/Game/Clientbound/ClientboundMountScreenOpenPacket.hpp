#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundMountScreenOpenPacket : public BasePacket<ClientboundMountScreenOpenPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Mount Screen Open";

        SERIALIZED_FIELD(ContainerId, VarInt);
        SERIALIZED_FIELD(InventoryColumns, VarInt);
        SERIALIZED_FIELD(EntityId, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
