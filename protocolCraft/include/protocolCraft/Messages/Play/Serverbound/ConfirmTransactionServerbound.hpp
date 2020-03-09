#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ConfirmTransactionServerbound : public BaseMessage<ConfirmTransactionServerbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x05;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x06;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x07;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x07;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Confirm Transaction (serverbound)";
        }

        void SetWindowId(const char c)
        {
            window_id = c;
        }

        void SetActionNumber(const short s)
        {
            action_number = s;
        }

        void SetAccepted(const bool b)
        {
            accepted = b;
        }

        const char GetWindowId() const
        {
            return window_id;
        }

        const short GetActionNumber() const
        {
            return action_number;
        }

        const bool GetAccepted() const
        {
            return accepted;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            window_id = ReadData<char>(iter, length);
            action_number = ReadData<short>(iter, length);
            accepted = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(window_id, container);
            WriteData<short>(action_number, container);
            WriteData<bool>(accepted, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["action_number"] = picojson::value((double)action_number);
            object["accepted"] = picojson::value(accepted);

            return value;
        }

    private:
        char window_id;
        short action_number;
        bool accepted;
    };
} //ProtocolCraft