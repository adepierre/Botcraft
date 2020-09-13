#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class WindowProperty : public BaseMessage<WindowProperty>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x15;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x16;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x15;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x16;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x15;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x14;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Window Property";
        }

        void SetWindowId(const unsigned char window_id_)
        {
            window_id = window_id_;
        }

        void SetProperty(const short property_)
        {
            property = property_;
        }

        void SetValue(const short value_)
        {
            value = value_;
        }


        const unsigned char GetWindowId() const
        {
            return window_id;
        }

        const short GetProperty() const
        {
            return property;
        }

        const short GetValue() const
        {
            return value;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            window_id = ReadData<unsigned char>(iter, length);
            property = ReadData<short>(iter, length);
            value = ReadData<short>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(window_id, container);
            WriteData<short>(property, container);
            WriteData<short>(value, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value val(picojson::object_type, false);
            picojson::object& object = val.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["property"] = picojson::value((double)property);
            object["value"] = picojson::value((double)value);

            return val;
        }

    private:
        unsigned char window_id;
        short property;
        short value;

    };
} //ProtocolCraft