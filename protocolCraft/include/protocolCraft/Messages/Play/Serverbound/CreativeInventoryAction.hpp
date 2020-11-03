#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class CreativeInventoryAction : public BaseMessage<CreativeInventoryAction>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x28;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Creative Inventory Action";
        }

        void SetSlot(const short slot_)
        {
            slot = slot_;
        }

        void SetClickedItem(const Slot& clicked_item_)
        {
            clicked_item = clicked_item_;
        }


        const short GetSlot() const
        {
            return slot;
        }

        const Slot& GetClickedItem() const
        {
            return clicked_item;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            slot = ReadData<short>(iter, length);
            clicked_item.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<short>(slot, container);
            clicked_item.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["slot"] = picojson::value((double)slot);
            object["clicked_item"] = picojson::value(clicked_item.Serialize());

            return value;
        }

    private:
        short slot;
        Slot clicked_item;

    };
} //ProtocolCraft