#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEquipmentPacket : public BaseMessage<ClientboundSetEquipmentPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Equipment";

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    private:
        std::map<unsigned char, Slot> ReadSlots(ReadIterator& iter, size_t& length) const
        {
            bool has_value = true;
            std::map<unsigned char, Slot> slots;
            while (has_value)
            {
                unsigned char current_value = ReadData<unsigned char>(iter, length);

                slots.insert({ static_cast<unsigned char>(current_value & 0x7F), ReadData<Slot>(iter, length) });

                has_value = current_value & (1 << 7);
            }
            return slots;
        }

        void WriteSlots(const std::map<unsigned char, Slot>& slots, WriteContainer& container) const
        {
            size_t index = 0;
            for (const auto& [k, v] : slots)
            {
                WriteData<unsigned char>(index != slots.size() - 1 ? k | (1 << 7) : k, container);
                WriteData<Slot>(v, container);
            }
        }
#endif

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        SERIALIZED_FIELD(Slot, std::pair<VarInt, ProtocolCraft::Slot>);
#else
        SERIALIZED_FIELD(Slots, Internal::CustomType<std::map<unsigned char, Slot>, &THIS::ReadSlots, &THIS::WriteSlots>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
