#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SteerVehicle : public BaseMessage<SteerVehicle>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x16;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x1D;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Steer Vehicle";
        }

        void SetSideways(const float sideways_)
        {
            sideways = sideways_;
        }

        void SetForward(const float forward_)
        {
            forward = forward_;
        }

        void SetFlags(const unsigned char flags_)
        {
            flags = flags_;
        }


        const float GetSideways() const
        {
            return sideways;
        }

        const float GetForward() const
        {
            return forward;
        }

        const unsigned char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            sideways = ReadData<float>(iter, length);
            forward = ReadData<float>(iter, length);
            flags = ReadData<unsigned char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(sideways, container);
            WriteData<float>(forward, container);
            WriteData<unsigned char>(flags, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["sideways"] = picojson::value((double)sideways);
            object["forward"] = picojson::value((double)forward);
            object["flags"] = picojson::value((double)flags);

            return value;
        }

    private:
        float sideways;
        float forward;
        unsigned char flags;

    };
} //ProtocolCraft