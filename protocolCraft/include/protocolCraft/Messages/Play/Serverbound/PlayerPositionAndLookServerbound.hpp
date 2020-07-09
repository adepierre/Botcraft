#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class PlayerPositionAndLookServerbound : public BaseMessage<PlayerPositionAndLookServerbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x11;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x12;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x12;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x13;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Position And Look (serverbound)";
        }

        void SetX(const double d)
        {
            x = d;
        }

        void SetFeetY(const double d)
        {
            feet_y = d;
        }

        void SetZ(const double d)
        {
            z = d;
        }

        void SetYaw(const float f)
        {
            yaw = f;
        }

        void SetPitch(const float f)
        {
            pitch = f;
        }

        void SetOnGround(const bool b)
        {
            on_ground = b;
        }

        const double GetZ() const
        {
            return z;
        }

        const double GetFeetY() const
        {
            return feet_y;
        }

        const double GetX() const
        {
            return x;
        }

        const float GetYaw() const
        {
            return yaw;
        }

        const float GetPitch() const
        {
            return pitch;
        }

        const bool GetOnGround() const
        {
            return on_ground;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<double>(iter, length);
            feet_y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yaw = ReadData<float>(iter, length);
            pitch = ReadData<float>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<double>(x, container);
            WriteData<double>(feet_y, container);
            WriteData<double>(z, container);
            WriteData<float>(yaw, container);
            WriteData<float>(pitch, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["x"] = picojson::value(x);
            object["feet_y"] = picojson::value(feet_y);
            object["z"] = picojson::value(z);
            object["yaw"] = picojson::value((double)yaw);
            object["pitch"] = picojson::value((double)pitch);
            object["on_ground"] = picojson::value(on_ground);

            return value;
        }

    private:
        double x;
        double feet_y;
        double z;

        float yaw;
        float pitch;
        bool on_ground;
    };
} //ProtocolCraft