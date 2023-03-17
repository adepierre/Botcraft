#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMoveVehiclePacket : public BaseMessage<ServerboundMoveVehiclePacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 // 1.16 or 1.16.1
        static constexpr int packet_id = 0x16; 
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x18;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Move Vehicle";

        virtual ~ServerboundMoveVehiclePacket() override
        {

        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetYRot(const float yRot_)
        {
            yRot = yRot_;
        }

        void SetXRot(const float xRot_)
        {
            xRot = xRot_;
        }


        double GetX() const
        {
            return x;
        }

        double GetY() const
        {
            return y;
        }

        double GetZ() const
        {
            return z;
        }

        float GetYRot() const
        {
            return yRot;
        }

        float GetXRot() const
        {
            return xRot;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yRot = ReadData<float>(iter, length);
            xRot = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<float>(yRot, container);
            WriteData<float>(xRot, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["yRot"] = yRot;
            output["xRot"] = xRot;

            return output;
        }

    private:
        double x;
        double y;
        double z;
        float yRot;
        float xRot;

    };
} //ProtocolCraft
