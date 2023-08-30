#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketPos : public BaseMessage<ServerboundMovePlayerPacketPos>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x14;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Move Player Pos";

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

        bool GetOnGround() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["on_ground"] = on_ground;

            return output;
        }

    private:
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        bool on_ground = false;

    };
} //ProtocolCraft
