#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEquipmentPacket : public BaseMessage<ClientboundSetEquipmentPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x3F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x42;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x46;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x47;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x47;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x47;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x50;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Equipment";
        }

        virtual ~ClientboundSetEquipmentPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

#if PROTOCOL_VERSION > 730
        void SetSlots(const std::vector<std::pair<unsigned char, Slot> >& slots_)
        {
            slots = slots_;
        }
#else
        void SetSlot(const std::pair<int, Slot>& slot_)
        {
            slot = slot_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

#if PROTOCOL_VERSION > 730
        const std::vector<std::pair<unsigned char, Slot> >& GetSlots() const
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

#if PROTOCOL_VERSION > 730
            bool has_value = true;
            slots = std::vector<std::pair<unsigned char, Slot> >(0);
            while (has_value)
            {
                unsigned char current_value = ReadData<unsigned char>(iter, length);
                
                std::pair<unsigned char, Slot> slot;
                slot.first = current_value & 0x7F;
                slot.second.Read(iter, length);
                slots.push_back(slot);

                has_value = current_value & (1 << 7);
            }
#else
            slot.first = ReadData<VarInt>(iter, length);
            slot.second.Read(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
#if PROTOCOL_VERSION > 730
            for (int i = 0; i < slots.size(); ++i)
            {
                WriteData<unsigned char>(i != slots.size() - 1 ? slots[i].first | (1 << 7) : slots[i].first, container);
                slots[i].second.Write(container);
            }
#else
            WriteData<VarInt>(slot.first, container);
            slot.second.Write(container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
#if PROTOCOL_VERSION > 730
            object["slots"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["slots"].get<picojson::array>();
            for (int i = 0; i < slots.size(); ++i)
            {
                picojson::value current_slot(picojson::object_type, false);
                picojson::object& current_slot_object = current_slot.get<picojson::object>();
                current_slot_object["first"] = picojson::value((double)slots[i].first);
                current_slot_object["second"] = slots[i].second.Serialize();
                array.push_back(current_slot);
            }
#else
            object["slot_first"] = picojson::value((double)slot.first);
            object["slot_second"] = slot.second.Serialize();
#endif

            return value;
        }

    private:
        int entity_id;
#if PROTOCOL_VERSION > 730
        std::vector<std::pair<unsigned char, Slot> > slots;
#else
        std::pair<int, Slot> slot;
#endif

    };
} //ProtocolCraft