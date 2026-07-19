#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCreativeModeSlotPacket : public BasePacket<ServerboundSetCreativeModeSlotPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Creative Mode Slot";

        SERIALIZED_FIELD(SlotNum, short);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SERIALIZED_FIELD(ItemStack, Slot);
#else
        SERIALIZED_FIELD(ItemStack, Internal::DiffType<Slot, UntrustedItemStack>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
