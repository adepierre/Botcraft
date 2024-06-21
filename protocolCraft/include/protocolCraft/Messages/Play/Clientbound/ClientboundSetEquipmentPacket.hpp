#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEquipmentPacket : public BaseMessage<ClientboundSetEquipmentPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Equipment";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (VarInt,   std::pair<VarInt, Slot>),
            (EntityId, Slot)
        );
#else
        DECLARE_FIELDS(
            (VarInt,   std::map<unsigned char, Slot>),
            (EntityId, Slots)
        );
#endif
        DECLARE_SERIALIZE;

        GETTER_SETTER(EntityId);
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        GETTER_SETTER(Slot);
#else
        GETTER_SETTER(Slots);
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetEntityId(ReadData<VarInt>(iter, length));

#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
            bool has_value = true;
            std::map<unsigned char, Slot> slots;
            while (has_value)
            {
                unsigned char current_value = ReadData<unsigned char>(iter, length);

                slots.insert({ static_cast<unsigned char>(current_value & 0x7F), ReadData<Slot>(iter, length) });

                has_value = current_value & (1 << 7);
            }
            SetSlots(slots);
#else
            const int slot_first = ReadData<VarInt>(iter, length);
            const Slot slot_second = ReadData<Slot>(iter, length);
            SetSlot({ slot_first, slot_second });
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetEntityId(), container);
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
            size_t index = 0;
            for (const auto& [k, v] : GetSlots())
            {
                WriteData<unsigned char>(index != GetSlots().size() - 1 ? k | (1 << 7) : k, container);
                WriteData<Slot>(v, container);
            }
#else
            WriteData<VarInt>(GetSlot().first, container);
            WriteData<Slot>(GetSlot().second, container);
#endif
        }
    };
} //ProtocolCraft
