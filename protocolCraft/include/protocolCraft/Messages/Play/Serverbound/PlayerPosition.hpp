#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class PlayerPosition : public BaseMessage<PlayerPosition>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x10;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x11;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x11;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x12;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x12;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Position";
        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetFeetY(const double feet_y_)
        {
            feet_y = feet_y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }


        const double GetX() const
        {
            return x;
        }

        const double GetFeetY() const
        {
            return feet_y;
        }

        const double GetZ() const
        {
            return z;
        }

        const bool GetOnGround() const
        {
            return on_ground;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            x = ReadData<double>(iter, length);
            feet_y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(x, container);
            WriteData<double>(feet_y, container);
            WriteData<double>(z, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["x"] = picojson::value(x);
            object["feet_y"] = picojson::value(feet_y);
            object["z"] = picojson::value(z);
            object["on_ground"] = picojson::value(on_ground);

            return value;
        }

    private:
        double x;
        double feet_y;
        double z;
        bool on_ground;

    };
} //ProtocolCraft