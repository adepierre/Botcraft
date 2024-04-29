#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundProjectilePowerPacket : public BaseMessage<ClientboundProjectilePowerPacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x79;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Projectile Power";

        virtual ~ClientboundProjectilePowerPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetXPower(const double x_power_)
        {
            x_power = x_power_;
        }

        void SetYPower(const double y_power_)
        {
            y_power = y_power_;
        }

        void SetZPower(const double z_power_)
        {
            z_power = z_power_;
        }


        int GetId_() const
        {
            return id_;
        }

        double GetXPower() const
        {
            return x_power;
        }

        double GetYPower() const
        {
            return y_power;
        }

        double GetZPower() const
        {
            return z_power;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            x_power = ReadData<double>(iter, length);
            y_power = ReadData<double>(iter, length);
            z_power = ReadData<double>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<double>(x_power, container);
            WriteData<double>(y_power, container);
            WriteData<double>(z_power, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id"] = id_;
            output["x_power"] = x_power;
            output["y_power"] = y_power;
            output["z_power"] = z_power;

            return output;
        }

    private:
        int id_ = 0;
        double x_power = 0.0;
        double y_power = 0.0;
        double z_power = 0.0;

    };
} //ProtocolCraft
#endif
