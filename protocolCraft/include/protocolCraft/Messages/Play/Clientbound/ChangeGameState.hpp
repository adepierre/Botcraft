#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ChangeGameState : public BaseMessage<ChangeGameState>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x20;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1F;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1E;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x1D;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Change Game State";
        }

        void SetReason(const unsigned char reason_)
        {
            reason = reason_;
        }

        void SetValue(const float value_)
        {
            value = value_;
        }


        const unsigned char GetReason() const
        {
            return reason;
        }

        const float GetValue() const
        {
            return value;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            reason = ReadData<unsigned char>(iter, length);
            value = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(reason, container);
            WriteData<float>(value, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value val(picojson::object_type, false);
            picojson::object& object = val.get<picojson::object>();

            object["reason"] = picojson::value((double)reason);
            object["value"] = picojson::value((double)value);

            return val;
        }

    private:
        unsigned char reason;
        float value;

    };
} //ProtocolCraft