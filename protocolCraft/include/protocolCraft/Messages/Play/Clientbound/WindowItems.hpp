#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class WindowItems : public BaseMessage<WindowItems>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x14;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x15;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x14;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x15;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x14;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x13;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Window Items";
        }

        void SetWindowId(const unsigned char window_id_)
        {
            window_id = window_id_;
        }

        void SetCount(const short count_)
        {
            count = count_;
        }

        void SetSlotData(const std::vector<Slot>& slot_data_)
        {
            slot_data = slot_data_;
        }

        const unsigned char GetWindowId() const
        {
            return window_id;
        }

        const short GetCount() const
        {
            return count;
        }

        const std::vector<Slot>& GetSlotData() const
        {
            return slot_data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            window_id = ReadData<unsigned char>(iter, length);
            count = ReadData<short>(iter, length);
            slot_data = std::vector<Slot>(count);
            for (int i = 0; i < count; ++i)
            {
                slot_data[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<unsigned char>(window_id, container);
            WriteData<short>(count, container);
            for (int i = 0; i < count; ++i)
            {
                slot_data[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["count"] = picojson::value((double)count);
            object["slot_data"] = picojson::value(picojson::array_type, false);

            picojson::array& array = object["slot_data"].get<picojson::array>();
            array.reserve(slot_data.size());

            for (int i = 0; i < slot_data.size(); ++i)
            {
                array.push_back(slot_data[i].Serialize());
            }

            return value;
        }

    private:
        unsigned char window_id;
        short count;
        std::vector<Slot> slot_data;
    };
} //ProtocolCraft