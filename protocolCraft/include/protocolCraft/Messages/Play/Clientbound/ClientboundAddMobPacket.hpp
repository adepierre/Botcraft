#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddMobPacket : public BaseMessage<ClientboundAddMobPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x03;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x03;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x03;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x03;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x02;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x02;
#elif PROTOCOL_VERSION == 755 // 1.17
            return 0x02;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Add Mob";
        }

        virtual ~ClientboundAddMobPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetUuid(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetType(const int type_)
        {
            type = type_;
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

        void SetYRot(const Angle yRot_)
        {
            yRot = yRot_;
        }

        void SetXRot(const Angle xRot_)
        {
            xRot = xRot_;
        }

        void SetYHeadRot(const Angle y_head_rot_)
        {
            y_head_rot = y_head_rot_;
        }

        void SetXd(const short xd_)
        {
            xd = xd_;
        }

        void SetYd(const short yd_)
        {
            yd = yd_;
        }

        void SetZd(const short zd_)
        {
            zd = zd_;
        }

#if PROTOCOL_VERSION < 550
        void SetRawMetadata(const std::vector<unsigned char>& raw_metadata_)
        {
            raw_metadata = raw_metadata_;
        }
#endif


        const int GetId_() const
        {
            return id_;
        }

        const UUID& GetEntityUuid() const
        {
            return uuid;
        }

        const int GetType() const
        {
            return type;
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

        const Angle GetYRot() const
        {
            return yRot;
        }

        const Angle GetXRot() const
        {
            return xRot;
        }

        const Angle GetYHeadRot() const
        {
            return y_head_rot;
        }

        const short GetXd() const
        {
            return xd;
        }

        const short GetYd() const
        {
            return yd;
        }

        const short GetZd() const
        {
            return zd;
        }

#if PROTOCOL_VERSION < 550
        const std::vector<unsigned char>& GetRawMetadata() const
        {
            return raw_metadata;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadVarInt(iter, length);
            uuid = ReadUUID(iter, length);
            type = ReadVarInt(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yRot = ReadData<Angle>(iter, length);
            xRot = ReadData<Angle>(iter, length);
            y_head_rot = ReadData<Angle>(iter, length);
            xd = ReadData<short>(iter, length);
            yd = ReadData<short>(iter, length);
            zd = ReadData<short>(iter, length);
#if PROTOCOL_VERSION < 550
                raw_metadata = ReadByteArray(iter, length, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(id_, container);
            WriteUUID(uuid, container);
            WriteVarInt(type, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<Angle>(yRot, container);
            WriteData<Angle>(xRot, container);
            WriteData<Angle>(y_head_rot, container);
            WriteData<short>(xd, container);
            WriteData<short>(yd, container);
            WriteData<short>(zd, container);
#if PROTOCOL_VERSION < 550
            WriteByteArray(raw_metadata, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["id_"] = picojson::value((double)id_);
            object["uuid"] = picojson::value(uuid);
            object["type"] = picojson::value((double)type);
            object["x"] = picojson::value(x);
            object["y"] = picojson::value(y);
            object["z"] = picojson::value(z);
            object["yRot"] = picojson::value((double)yRot);
            object["xRot"] = picojson::value((double)xRot);
            object["y_head_rot"] = picojson::value((double)y_head_rot);
            object["xd"] = picojson::value((double)xd);
            object["yd"] = picojson::value((double)yd);
            object["zd"] = picojson::value((double)zd);
#if PROTOCOL_VERSION < 550
            object["raw_metadata"] = picojson::value("Vector of " + std::to_string(raw_metadata.size()) + " unsigned char");
#endif

            return value;
        }

    private:
        int id_;
        UUID uuid;
        int type;
        double x;
        double y;
        double z;
        short xd;
        short yd;
        short zd;
        Angle yRot;
        Angle xRot;
        Angle y_head_rot;
#if PROTOCOL_VERSION < 550
        std::vector<unsigned char> raw_metadata;
#endif

    };
} //ProtocolCraft