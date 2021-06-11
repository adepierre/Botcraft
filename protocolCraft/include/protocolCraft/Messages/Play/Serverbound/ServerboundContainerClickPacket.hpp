#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

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
#elif PROTOCOL_VERSION == 755 // 1.17
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

        void SetUid(const short uid_)
        {
            uid = uid_;
        }

        void SetClickType(const int click_type_)
        {
            click_type = click_type_;
        }

        void SetItemStack(const Slot& item_stack_)
        {
            item_stack = item_stack_;
        }


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

        const short GetUid() const
        {
            return uid;
        }

        const int GetClickType() const
        {
            return click_type;
        }

        const Slot& GetItemStack() const
        {
            return item_stack;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<unsigned char>(iter, length);
            slot_num = ReadData<short>(iter, length);
            button_num = ReadData<char>(iter, length);
            uid = ReadData<short>(iter, length);
            click_type = ReadVarInt(iter, length);
            item_stack.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(container_id, container);
            WriteData<short>(slot_num, container);
            WriteData<char>(button_num, container);
            WriteData<short>(uid, container);
            WriteVarInt(click_type, container);
            item_stack.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["container_id"] = picojson::value((double)container_id);
            object["slot_num"] = picojson::value((double)slot_num);
            object["button_num"] = picojson::value((double)button_num);
            object["uid"] = picojson::value((double)uid);
            object["click_type"] = picojson::value((double)click_type);
            object["item_stack"] = item_stack.Serialize();

            return value;
        }

    private:
        unsigned char container_id;
        short slot_num;
        char button_num;
        short uid;
        Slot item_stack;
        int click_type;

    };
} //ProtocolCraft