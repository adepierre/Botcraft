#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderCenterPacket : public BaseMessage<ClientboundSetBorderCenterPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x43;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Border Center";

        virtual ~ClientboundSetBorderCenterPacket() override
        {

        }


        void SetNewCenterX(const double new_center_x_)
        {
            new_center_x = new_center_x_;
        }

        void SetNewCenterZ(const double new_center_z_)
        {
            new_center_z = new_center_z_;
        }


        double GetNewCenterX() const
        {
            return new_center_x;
        }

        double GetNewCenterZ() const
        {
            return new_center_z;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            new_center_x = ReadData<double>(iter, length);
            new_center_z = ReadData<double>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(new_center_x, container);
            WriteData<double>(new_center_z, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["new_center_x"] = new_center_x;
            output["new_center_z"] = new_center_z;

            return output;
        }

    private:
        double new_center_x;
        double new_center_z;

    };
} //ProtocolCraft
#endif
