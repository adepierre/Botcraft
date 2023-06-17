#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCreativeModeSlotPacket : public BaseMessage<ServerboundSetCreativeModeSlotPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x2B;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Creative Mode Slot";

        virtual ~ServerboundSetCreativeModeSlotPacket() override
        {

        }

        void SetSlotNum(const short slot_num_)
        {
            slot_num = slot_num_;
        }

        void SetItemStack(const Slot& item_stack_)
        {
            item_stack = item_stack_;
        }


        short GetSlotNum() const
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
            item_stack = ReadData<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<short>(slot_num, container);
            WriteData<Slot>(item_stack, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["slot_num"] = slot_num;
            output["item_stack"] = item_stack;

            return output;
        }

    private:
        short slot_num = 0;
        Slot item_stack;

    };
} //ProtocolCraft
