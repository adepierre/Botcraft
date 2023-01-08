#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTeleportEntityPacket : public BaseMessage<ClientboundTeleportEntityPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x62;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x66;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x64;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Teleport Entity";

        virtual ~ClientboundTeleportEntityPacket() override
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

        void SetYRot(const unsigned char yRot_)
        {
            yRot = yRot_;
        }

        void SetXRot(const unsigned char xRot_)
        {
            xRot = xRot_;
        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }

        const int GetId_() const
        {
            return id_;
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

        const unsigned char GetYRot() const
        {
            return yRot;
        }

        const unsigned char GetXRot() const
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
            id_ = ReadData<VarInt>(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yRot = ReadData<unsigned char>(iter, length);
            xRot = ReadData<unsigned char>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<unsigned char>(yRot, container);
            WriteData<unsigned char>(xRot, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["id_"] = id_;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["yRot"] = yRot;
            output["xRot"] = xRot;
            output["on_ground"] = on_ground;

            return output;
        }

    private:
        int id_;
        double x;
        double y;
        double z;
        unsigned char yRot;
        unsigned char xRot;
        bool on_ground;
    };
} //ProtocolCraft
