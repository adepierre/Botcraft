#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddEntityPacket : public BaseMessage<ClientboundAddEntityPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x00;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x00;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Add Entity";

        virtual ~ClientboundAddEntityPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetUUID(const UUID& uuid_)
        {
            uuid = uuid_;
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

        void SetXa(const short xa_)
        {
            xa = xa_;
        }

        void SetYa(const short ya_)
        {
            ya = ya_;
        }

        void SetZa(const short za_)
        {
            za = za_;
        }

        void SetXRot(const Angle xRot_)
        {
            x_rot = xRot_;
        }

        void SetYRot(const Angle yRot_)
        {
            y_rot = yRot_;
        }

#if PROTOCOL_VERSION > 758
        void SetYHeadRot(const Angle y_head_rot_)
        {
            y_head_rot = y_head_rot_;
        }
#endif

        void SetType(const char type_)
        {
            type = type_;
        }

        void SetData(const int data_)
        {
            data = data_;
        }

        int GetId_() const
        {
            return id_;
        }

        const UUID& GetUUID() const
        {
            return uuid;
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

        short GetXa() const
        {
            return xa;
        }

        short GetYa() const
        {
            return ya;
        }

        short GetZa() const
        {
            return za;
        }

        Angle GetXRot() const
        {
            return x_rot;
        }

        Angle GetYRot() const
        {
            return y_rot;
        }

#if PROTOCOL_VERSION > 758
        Angle GetYHeadRot() const
        {
            return y_head_rot;
        }
#endif

        char GetType() const
        {
            return type;
        }

        int GetData() const
        {
            return data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            uuid = ReadData<UUID>(iter, length);
#if PROTOCOL_VERSION < 458
            type = ReadData<char>(iter, length);
#else
            type = ReadData<VarInt>(iter, length);
#endif
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            x_rot = ReadData<Angle>(iter, length);
            y_rot = ReadData<Angle>(iter, length);
#if PROTOCOL_VERSION > 758
            y_head_rot = ReadData<Angle>(iter, length);
            data = ReadData<VarInt>(iter, length);
#else
            data = ReadData<int>(iter, length);
#endif
            xa = ReadData<short>(iter, length);
            ya = ReadData<short>(iter, length);
            za = ReadData<short>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<UUID>(uuid, container);
#if PROTOCOL_VERSION < 458
            WriteData<char>(type, container);
#else
            WriteData<VarInt>(type, container);
#endif
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<Angle>(x_rot, container);
            WriteData<Angle>(y_rot, container);
#if PROTOCOL_VERSION > 758
            WriteData<Angle>(y_head_rot, container);
            WriteData<VarInt>(data, container);
#else
            WriteData<int>(data, container);
#endif
            WriteData<short>(xa, container);
            WriteData<short>(ya, container);
            WriteData<short>(za, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;
            output["uuid"] = uuid;
            output["type"] = type;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["x_rot"] = x_rot;
            output["y_rot"] = y_rot;
#if PROTOCOL_VERSION > 758
            output["y_head_rot"] = y_head_rot;
#endif
            output["data"] = data;
            output["xa"] = xa;
            output["ya"] = ya;
            output["za"] = za;

            return output;
    }

    private:
        int id_;
        UUID uuid;
#if PROTOCOL_VERSION < 458
        char type;
#else
        int type;
#endif
        double x;
        double y;
        double z;
        short xa;
        short ya;
        short za;
        Angle x_rot;
        Angle y_rot;
#if PROTOCOL_VERSION > 758
        Angle y_head_rot;
#endif
        int data;

    };
} //ProtocolCraft
