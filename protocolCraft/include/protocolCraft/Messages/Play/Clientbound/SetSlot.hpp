#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class SetSlot : public BaseMessage<SetSlot>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x16;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Slot";
        }

        void SetWindowId(const char window_id_)
        {
            window_id = window_id_;
        }

        void SetSlot_(const short slot_)
        {
            slot = slot_;
        }

        void SetSlotData(const Slot& slot_data_)
        {
            slot_data = slot_data_;
        }

        const char GetWindowId() const
        {
            return window_id;
        }

        const short GetSlot() const
        {
            return slot;
        }

        const Slot& GetSlotData() const
        {
            return slot_data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            window_id = ReadData<char>(iter, length);
            slot = ReadData<short>(iter, length);
            slot_data.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(window_id, container);
            WriteData<short>(slot, container);
            slot_data.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["slot"] = picojson::value((double)slot);
            object["slot_data"] = slot_data.Serialize();

            return value;
        }

    private:
        char window_id;
        short slot;
        Slot slot_data;

    };
} //ProtocolCraft