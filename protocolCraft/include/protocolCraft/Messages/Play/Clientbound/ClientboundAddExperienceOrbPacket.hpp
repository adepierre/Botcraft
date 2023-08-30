#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddExperienceOrbPacket : public BaseMessage<ClientboundAddExperienceOrbPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 || PROTOCOL_VERSION == 393 ||  \
      PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 ||  \
      PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 ||  \
      PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754 || PROTOCOL_VERSION == 755 ||  \
      PROTOCOL_VERSION == 756 || PROTOCOL_VERSION == 757 ||  \
      PROTOCOL_VERSION == 758 || PROTOCOL_VERSION == 759 ||  \
      PROTOCOL_VERSION == 760 || PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x02;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Add Experience Orb";

        virtual ~ClientboundAddExperienceOrbPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
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

        void SetValue(const short value__)
        {
            value_ = value__;
        }


        int GetId_() const
        {
            return id_;
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

        short GetValue() const
        {
            return value_;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            value_ = ReadData<short>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<short>(value_, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["value"] = value_;

            return output;
        }

    private:
        int id_ = 0;
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        short value_ = 0;

    };
} //ProtocolCraft
