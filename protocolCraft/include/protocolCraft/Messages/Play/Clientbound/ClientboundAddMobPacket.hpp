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

#if PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS_TYPES(VarInt, UUID, VarInt, double, double, double, Angle, Angle, Angle,    short, short, short, std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(Id_,    Uuid, Type,   X,      Y,      Z,      YRot,  XRot,  YHeadRot, Xd,    Yd,    Zd,    RawMetadata);
        DECLARE_SERIALIZE;
#else
        DECLARE_FIELDS_TYPES(VarInt, UUID, VarInt, double, double, double, Angle, Angle, Angle,    short, short, short);
        DECLARE_FIELDS_NAMES(Id_,    Uuid, Type,   X,      Y,      Z,      YRot,  XRot,  YHeadRot, Xd,    Yd,    Zd);
        DECLARE_READ_WRITE_SERIALIZE;
#endif

        GETTER_SETTER(Id_);
        GETTER_SETTER(Uuid);
        GETTER_SETTER(Type);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
        GETTER_SETTER(YHeadRot);
        GETTER_SETTER(Xd);
        GETTER_SETTER(Yd);
        GETTER_SETTER(Zd);
#if PROTOCOL_VERSION < 573 /* < 1.15 */
        GETTER_SETTER(RawMetadata);
#endif
    protected:
#if PROTOCOL_VERSION < 550 /* < 1.15 */
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetId_(ReadData<VarInt>(iter, length));
            SetUUID(ReadData<UUID>(iter, length));
            SetType(ReadData<VarInt>(iter, length));
            SetX(ReadData<double>(iter, length));
            SetY(ReadData<double>(iter, length));
            SetZ(ReadData<double>(iter, length));
            SetYRot(ReadData<Angle>(iter, length));
            SetXRot(ReadData<Angle>(iter, length));
            SetYHeadRot(ReadData<Angle>(iter, length));
            SetXd(ReadData<short>(iter, length));
            SetYd(ReadData<short>(iter, length));
            SetZd(ReadData<short>(iter, length));
            SetRawMetadata(ReadByteArray(iter, length, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetId_(), container);
            WriteData<UUID>(GetUUID(), container);
            WriteData<VarInt>(GetType(), container);
            WriteData<double>(GetX(), container);
            WriteData<double>(GetY(), container);
            WriteData<double>(GetZ(), container);
            WriteData<Angle>(GetYRot(), container);
            WriteData<Angle>(GetXRot(), container);
            WriteData<Angle>(GetYHeadRot(), container);
            WriteData<short>(GetXd(), container);
            WriteData<short>(GetYd(), container);
            WriteData<short>(GetZd(), container);
            WriteByteArray(GetRawMetadata(), container);
        }
#endif
    };
} //ProtocolCraft
#endif
