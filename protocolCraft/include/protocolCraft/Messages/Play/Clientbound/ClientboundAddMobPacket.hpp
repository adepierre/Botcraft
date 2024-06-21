#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddMobPacket : public BaseMessage<ClientboundAddMobPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Add Mob";

#if PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS(
            (VarInt, UUID, VarInt, double, double, double, unsigned char, unsigned char, unsigned char,    short, short, short, std::vector<unsigned char>),
            (Id_,    Uuid, Type,   X,      Y,      Z,      YRot,          XRot,                  YHeadRot, Xd,    Yd,    Zd,    RawMetadata)
        );
        DECLARE_SERIALIZE;
#else
        DECLARE_FIELDS(
            (VarInt, UUID, VarInt, double, double, double, unsigned char, unsigned char, unsigned char,    short, short, short),
            (Id_,    Uuid, Type,   X,      Y,      Z,      YRot,          XRot,                  YHeadRot, Xd,    Yd,    Zd)
        );
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
            SetUuid(ReadData<UUID>(iter, length));
            SetType(ReadData<VarInt>(iter, length));
            SetX(ReadData<double>(iter, length));
            SetY(ReadData<double>(iter, length));
            SetZ(ReadData<double>(iter, length));
            SetYRot(ReadData<unsigned char>(iter, length));
            SetXRot(ReadData<unsigned char>(iter, length));
            SetYHeadRot(ReadData<unsigned char>(iter, length));
            SetXd(ReadData<short>(iter, length));
            SetYd(ReadData<short>(iter, length));
            SetZd(ReadData<short>(iter, length));
            SetRawMetadata(ReadByteArray(iter, length, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetId_(), container);
            WriteData<UUID>(GetUuid(), container);
            WriteData<VarInt>(GetType(), container);
            WriteData<double>(GetX(), container);
            WriteData<double>(GetY(), container);
            WriteData<double>(GetZ(), container);
            WriteData<unsigned char>(GetYRot(), container);
            WriteData<unsigned char>(GetXRot(), container);
            WriteData<unsigned char>(GetYHeadRot(), container);
            WriteData<short>(GetXd(), container);
            WriteData<short>(GetYd(), container);
            WriteData<short>(GetZd(), container);
            WriteByteArray(GetRawMetadata(), container);
        }
#endif
    };
} //ProtocolCraft
#endif
