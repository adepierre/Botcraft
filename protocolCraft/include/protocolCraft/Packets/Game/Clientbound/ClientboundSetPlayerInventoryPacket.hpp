#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundSetPlayerInventoryPacket : public BasePacket<ClientboundSetPlayerInventoryPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Player Inventory";

        SERIALIZED_FIELD(Slot, VarInt);
        SERIALIZED_FIELD(Contents, ProtocolCraft::Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
