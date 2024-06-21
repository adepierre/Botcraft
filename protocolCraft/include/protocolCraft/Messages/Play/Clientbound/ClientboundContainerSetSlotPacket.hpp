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

#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        DECLARE_FIELDS(
            (char,        short, Slot),
            (ContainerId, Slot,  ItemStack)
        );
#else
        DECLARE_FIELDS(
            (char,        VarInt,  short, Slot),
            (ContainerId, StateId, Slot,  ItemStack)
        );

#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Slot);
        GETTER_SETTER(ItemStack);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        GETTER_SETTER(StateId);
#endif
    };
} //ProtocolCraft
