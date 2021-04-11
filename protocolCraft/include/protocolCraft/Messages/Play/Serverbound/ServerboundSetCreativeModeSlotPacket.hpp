#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCreativeModeSlotPacket : public BaseMessage<ServerboundSetCreativeModeSlotPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x24;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x26;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x26;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x27;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x28;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Creative Mode Slot";
        }

        void SetSlotNum(const short slot_num_)
        {
            slot_num = slot_num_;
        }

        void SetItemStack(const Slot& item_stack_)
        {
            item_stack = item_stack_;
        }


        const short GetSlotNum() const
        {
            return slot_num;
        }

        const Slot& GetItemStack() const
        {
            return item_stack;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            slot_num = ReadData<short>(iter, length);
            item_stack.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<short>(slot_num, container);
            item_stack.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["slot_num"] = picojson::value((double)slot_num);
            object["item_stack"] = picojson::value(item_stack.Serialize());

            return value;
        }

    private:
        short slot_num;
        Slot item_stack;

    };
} //ProtocolCraft