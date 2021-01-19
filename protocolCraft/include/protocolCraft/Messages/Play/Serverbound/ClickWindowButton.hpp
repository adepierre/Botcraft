#pragma once

#if PROTOCOL_VERSION > 476
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClickWindowButton : public BaseMessage<ClickWindowButton>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x08;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x08;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x08;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x08;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Click Window Button";
        }

        void SetWindowId(const char window_id_)
        {
            window_id = window_id_;
        }

        void SetButtonId(const char button_id_)
        {
            button_id = button_id_;
        }


        const char GetWindowId() const
        {
            return window_id;
        }

        const char GetButtonId() const
        {
            return button_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            window_id = ReadData<char>(iter, length);
            button_id = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(window_id, container);
            WriteData<char>(button_id, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["button_id"] = picojson::value((double)button_id);

            return value;
        }

    private:
        char window_id;
        char button_id;

    };
} //ProtocolCraft
#endif
