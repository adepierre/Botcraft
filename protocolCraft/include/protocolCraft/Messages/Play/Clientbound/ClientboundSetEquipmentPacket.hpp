#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEquipmentPacket : public BaseMessage<ClientboundSetEquipmentPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x46;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x51;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x59;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x5B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Equipment";

        virtual ~ClientboundSetEquipmentPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
        void SetSlots(const std::map<unsigned char, Slot>& slots_)
        {
            slots = slots_;
        }
#else
        void SetSlot(const std::pair<int, Slot>& slot_)
        {
            slot = slot_;
        }
#endif


        int GetEntityId() const
        {
            return entity_id;
        }

#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
        const std::map<unsigned char, Slot>& GetSlots() const
        {
            return slots;
        }
#else
        const std::pair<int, Slot>& GetSlot() const
        {
            return slot;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);

#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
            bool has_value = true;
            slots.clear();
            while (has_value)
            {
                unsigned char current_value = ReadData<unsigned char>(iter, length);

                slots.insert({ current_value & 0x7F, ReadData<Slot>(iter, length) });

                has_value = current_value & (1 << 7);
            }
#else
            slot.first = ReadData<VarInt>(iter, length);
            slot.second = ReadData<Slot>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
            size_t index = 0;
            for (const auto& [k, v] : slots)
            {
                WriteData<unsigned char>(index != slots.size() - 1 ? k | (1 << 7) : k, container);
                WriteData<Slot>(v, container);
            }
#else
            WriteData<VarInt>(slot.first, container);
            WriteData<Slot>(slot.second, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
            output["slots"] = Json::Object();

            for (const auto& [k, v] : slots)
            {
                output["slots"][std::to_string(k)] = v;
            }
#else
            output["slot_first"] = slot.first;
            output["slot_second"] = slot.second;
#endif

            return output;
        }

    private:
        int entity_id = 0;
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */
        std::map<unsigned char, Slot> slots;
#else
        std::pair<int, Slot> slot;
#endif

    };
} //ProtocolCraft
