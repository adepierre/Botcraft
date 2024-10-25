#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetSlotPacket : public BaseMessage<ClientboundContainerSetSlotPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Set Slot";

        SERIALIZED_FIELD(ContainerId, char);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        SERIALIZED_FIELD(StateId, VarInt);
#endif
        SERIALIZED_FIELD(Slot, short);
        SERIALIZED_FIELD(ItemStack, ProtocolCraft::Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
