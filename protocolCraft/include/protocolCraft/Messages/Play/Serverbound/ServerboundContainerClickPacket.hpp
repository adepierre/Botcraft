#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"
#if PROTOCOL_VERSION > 754
#include <map>
#endif

namespace ProtocolCraft
{
    class ServerboundContainerClickPacket : public BaseMessage<ServerboundContainerClickPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x07;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x08;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x09;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x09;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x09;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x09;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x08;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Container Click";
        }

        virtual ~ServerboundContainerClickPacket() override
        {

        }

        void SetContainerId(const unsigned char container_id_)
        {
            container_id = container_id_;
        }

        void SetSlotNum(const short slot_num_)
        {
            slot_num = slot_num_;
        }

        void SetButtonNum(const char button_num_)
        {
            button_num = button_num_;
        }

#if PROTOCOL_VERSION < 755
        void SetUid(const short uid_)
        {
            uid = uid_;
        }
#endif

        void SetClickType(const int click_type_)
        {
            click_type = click_type_;
        }

#if PROTOCOL_VERSION > 754
        void SetChangedSlots(const std::map<short, Slot>& changed_slots_)
        {
            changed_slots = changed_slots_;
        }
#endif

#if PROTOCOL_VERSION < 755
        void SetItemStack(const Slot& item_stack_)
        {
            item_stack = item_stack_;
        }
#else
        void SetCarriedItem(const Slot& carried_item_)
        {
            carried_item = carried_item_;
        }
#endif

#if PROTOCOL_VERSION > 755
        void SetStateId(const int state_id_)
        {
            state_id = state_id_;
        }
#endif

        const unsigned char GetContainerId() const
        {
            return container_id;
        }

        const short GetSlotNum() const
        {
            return slot_num;
        }

        const char GetButtonNum() const
        {
            return button_num;
        }

#if PROTOCOL_VERSION < 755
        const short GetUid() const
        {
            return uid;
        }
#endif

        const int GetClickType() const
        {
            return click_type;
        }

#if PROTOCOL_VERSION > 754
        const std::map<short, Slot>& GetChangeSlots() const
        {
            return changed_slots;
        }
#endif

#if PROTOCOL_VERSION < 755
        const Slot& GetItemStack() const
        {
            return item_stack;
        }
#else
        const Slot& GetCarriedItem() const
        {
            return carried_item;
        }
#endif

#if PROTOCOL_VERSION > 755
        const int GetStateId() const
        {
            return state_id;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION > 755
            state_id = ReadVarInt(iter, length);
#endif
            slot_num = ReadData<short>(iter, length);
            button_num = ReadData<char>(iter, length);
#if PROTOCOL_VERSION < 755
            uid = ReadData<short>(iter, length);
#endif
            click_type = ReadVarInt(iter, length);
#if PROTOCOL_VERSION > 754
            changed_slots.clear();
            const int changed_slots_size = ReadVarInt(iter, length);
            for (int i = 0; i < changed_slots_size; ++i)
            {
                changed_slots[ReadData<short>(iter, length)].Read(iter, length);
            }
#endif
#if PROTOCOL_VERSION < 755
            item_stack.Read(iter, length);
#else
            carried_item.Read(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(container_id, container);
#if PROTOCOL_VERSION > 755
            WriteVarInt(state_id, container);
#endif
            WriteData<short>(slot_num, container);
            WriteData<char>(button_num, container);
#if PROTOCOL_VERSION < 755
            WriteData<short>(uid, container);
#endif
            WriteVarInt(click_type, container);
#if PROTOCOL_VERSION > 754
            WriteVarInt(changed_slots.size(), container);
            for (auto it = changed_slots.begin(); it != changed_slots.end(); ++it)
            {
                WriteData<short>(it->first, container);
                it->second.Write(container);
            }
#endif
#if PROTOCOL_VERSION < 755
            item_stack.Write(container);
#else
            carried_item.Write(container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["container_id"] = picojson::value((double)container_id);
#if PROTOCOL_VERSION > 755
            object["state_id"] = picojson::value((double)state_id);
#endif
            object["slot_num"] = picojson::value((double)slot_num);
            object["button_num"] = picojson::value((double)button_num);
#if PROTOCOL_VERSION < 755
            object["uid"] = picojson::value((double)uid);
#endif
            object["click_type"] = picojson::value((double)click_type);
#if PROTOCOL_VERSION > 754
            object["changed_slots"] = picojson::value(picojson::object_type, false);
            picojson::object& changed_slots_object = object["changed_slots"].get<picojson::object>();

            for (auto it = changed_slots.begin(); it != changed_slots.end(); ++it)
            {
                changed_slots_object[std::to_string(it->first)] = it->second.Serialize();
            }
#endif
#if PROTOCOL_VERSION < 755
            object["item_stack"] = item_stack.Serialize();
#else
            object["carried_item"] = carried_item.Serialize();
#endif

            return value;
        }

    private:
        unsigned char container_id;
#if PROTOCOL_VERSION > 755
        int state_id;
#endif
        short slot_num;
        char button_num;
#if PROTOCOL_VERSION < 755
        short uid;
#endif
#if PROTOCOL_VERSION < 755
        Slot item_stack;
#else
        Slot carried_item;
#endif
#if PROTOCOL_VERSION > 754
        std::map<short, Slot> changed_slots;
#endif
        int click_type;

    };
} //ProtocolCraft