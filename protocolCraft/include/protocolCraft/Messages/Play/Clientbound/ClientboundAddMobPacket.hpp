#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddMobPacket : public BaseMessage<ClientboundAddMobPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x02;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Add Mob";

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
            y_rot = yRot_;
        }

        void SetXRot(const Angle xRot_)
        {
            x_rot = xRot_;
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

#if PROTOCOL_VERSION < 550 /* < 1.15 */
        void SetRawMetadata(const std::vector<unsigned char>& raw_metadata_)
        {
            raw_metadata = raw_metadata_;
        }
#endif


        int GetId_() const
        {
            return id_;
        }

        const UUID& GetEntityUuid() const
        {
            return uuid;
        }

        int GetType() const
        {
            return type;
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

        Angle GetYRot() const
        {
            return y_rot;
        }

        Angle GetXRot() const
        {
            return x_rot;
        }

        Angle GetYHeadRot() const
        {
            return y_head_rot;
        }

        short GetXd() const
        {
            return xd;
        }

        short GetYd() const
        {
            return yd;
        }

        short GetZd() const
        {
            return zd;
        }

#if PROTOCOL_VERSION < 550 /* < 1.15 */
        const std::vector<unsigned char>& GetRawMetadata() const
        {
            return raw_metadata;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            uuid = ReadData<UUID>(iter, length);
            type = ReadData<VarInt>(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            y_rot = ReadData<Angle>(iter, length);
            x_rot = ReadData<Angle>(iter, length);
            y_head_rot = ReadData<Angle>(iter, length);
            xd = ReadData<short>(iter, length);
            yd = ReadData<short>(iter, length);
            zd = ReadData<short>(iter, length);
#if PROTOCOL_VERSION < 550 /* < 1.15 */
            raw_metadata = ReadByteArray(iter, length, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<UUID>(uuid, container);
            WriteData<VarInt>(type, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<Angle>(y_rot, container);
            WriteData<Angle>(x_rot, container);
            WriteData<Angle>(y_head_rot, container);
            WriteData<short>(xd, container);
            WriteData<short>(yd, container);
            WriteData<short>(zd, container);
#if PROTOCOL_VERSION < 550 /* < 1.15 */
            WriteByteArray(raw_metadata, container);
#endif
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
            output["y_rot"] = y_rot;
            output["x_rot"] = x_rot;
            output["y_head_rot"] = y_head_rot;
            output["xd"] = xd;
            output["yd"] = yd;
            output["zd"] = zd;
#if PROTOCOL_VERSION < 550 /* < 1.15 */
            output["raw_metadata"] = "Vector of " + std::to_string(raw_metadata.size()) + " unsigned char";
#endif

            return output;
        }

    private:
        int id_ = 0;
        UUID uuid = {};
        int type = 0;
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        short xd = 0;
        short yd = 0;
        short zd = 0;
        Angle y_rot = 0;
        Angle x_rot = 0;
        Angle y_head_rot = 0;
#if PROTOCOL_VERSION < 550 /* < 1.15 */
        std::vector<unsigned char> raw_metadata;
#endif

    };
} //ProtocolCraft
#endif
