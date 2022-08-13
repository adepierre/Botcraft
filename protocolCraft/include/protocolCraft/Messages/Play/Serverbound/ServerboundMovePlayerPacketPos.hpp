#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketPos : public BaseMessage<ServerboundMovePlayerPacketPos>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x12;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x12;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x11;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x11;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x13;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x14;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Move Player Pos";
        }

        virtual ~ServerboundMovePlayerPacketPos() override
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

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }


        const double GetX() const
        {
            return x;
        }

        const double GetY() const
        {
            return y;
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
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["on_ground"] = on_ground;

            return output;
        }

    private:
        double x;
        double y;
        double z;
        bool on_ground;

    };
} //ProtocolCraft