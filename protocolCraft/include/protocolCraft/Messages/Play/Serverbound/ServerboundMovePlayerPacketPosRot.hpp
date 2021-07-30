#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketPosRot : public BaseMessage<ServerboundMovePlayerPacketPosRot>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x13;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x13;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x12;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Move Player PosRot";
        }

        virtual ~ServerboundMovePlayerPacketPosRot() override
        {

        }

        void SetX(const double d)
        {
            x = d;
        }

        void SetY(const double d)
        {
            y = d;
        }

        void SetZ(const double d)
        {
            z = d;
        }

        void SetYRot(const float f)
        {
            yRot = f;
        }

        void SetXRot(const float f)
        {
            xRot = f;
        }

        void SetOnGround(const bool b)
        {
            on_ground = b;
        }

        const double GetZ() const
        {
            return z;
        }

        const double GetY() const
        {
            return y;
        }

        const double GetX() const
        {
            return x;
        }

        const float GetYRot() const
        {
            return yRot;
        }

        const float GetXRot() const
        {
            return xRot;
        }

        const bool GetOnGround() const
        {
            return on_ground;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yRot = ReadData<float>(iter, length);
            xRot = ReadData<float>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<float>(yRot, container);
            WriteData<float>(xRot, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["x"] = picojson::value(x);
            object["y"] = picojson::value(y);
            object["z"] = picojson::value(z);
            object["yRot"] = picojson::value((double)yRot);
            object["xRot"] = picojson::value((double)xRot);
            object["on_ground"] = picojson::value(on_ground);

            return value;
        }

    private:
        double x;
        double y;
        double z;
        float yRot;
        float xRot;
        bool on_ground;
    };
} //ProtocolCraft