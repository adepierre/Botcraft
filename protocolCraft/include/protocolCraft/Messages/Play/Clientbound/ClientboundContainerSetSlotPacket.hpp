#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetSlotPacket : public BaseMessage<ClientboundContainerSetSlotPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x14;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Container Set Slot";

        virtual ~ClientboundContainerSetSlotPacket() override
        {

        }

        void SetContainerId(const char container_id_)
        {
            container_id = container_id_;
        }

        void SetSlot_(const short slot_)
        {
            slot = slot_;
        }

        void SetItemStack(const Slot& item_stack_)
        {
            item_stack = item_stack_;
        }

#if PROTOCOL_VERSION > 755
        void SetStateId(const int state_id_)
        {
            state_id = state_id_;
        }
#endif

        char GetContainerId() const
        {
            return container_id;
        }

        short GetSlot() const
        {
            return slot;
        }

        const Slot& GetItemStack() const
        {
            return item_stack;
        }

#if PROTOCOL_VERSION > 755
        int GetStateId() const
        {
            return state_id;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            container_id = ReadData<char>(iter, length);
#if PROTOCOL_VERSION > 755
            state_id = ReadData<VarInt>(iter, length);
#endif
            slot = ReadData<short>(iter, length);
            item_stack = ReadData<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(container_id, container);
#if PROTOCOL_VERSION > 755
            WriteData<VarInt>(state_id, container);
#endif
            WriteData<short>(slot, container);
            WriteData<Slot>(item_stack, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["slot"] = slot;
            output["item_stack"] = item_stack;
#if PROTOCOL_VERSION > 755
            output["state_id"] = state_id;
#endif

            return output;
        }

    private:
        char container_id;
        short slot;
        Slot item_stack;
#if PROTOCOL_VERSION > 755
        int state_id;
#endif

    };
} //ProtocolCraft
