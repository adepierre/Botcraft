#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetSlotPacket : public BaseMessage<ClientboundContainerSetSlotPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x16;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x17;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x16;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x17;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x16;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x15;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x16;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Container Set Slot";
        }

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

        const char GetContainerId() const
        {
            return container_id;
        }

        const short GetSlot() const
        {
            return slot;
        }

        const Slot& GetItemStack() const
        {
            return item_stack;
        }

#if PROTOCOL_VERSION > 755
        const int GetStateId() const
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
            item_stack.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(container_id, container);
#if PROTOCOL_VERSION > 755
            WriteData<VarInt>(state_id, container);
#endif
            WriteData<short>(slot, container);
            item_stack.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["container_id"] = picojson::value((double)container_id);
            object["slot"] = picojson::value((double)slot);
            object["item_stack"] = item_stack.Serialize();
#if PROTOCOL_VERSION > 755
            object["state_id"] = picojson::value((double)state_id);
#endif

            return value;
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