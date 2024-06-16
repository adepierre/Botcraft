#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPlayerPacket : public BaseMessage<ClientboundAddPlayerPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */ ||  \
      PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x03;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Add Player";

#if PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS(
            (VarInt,   UUID,     double, double, double, unsigned char, unsigned char, std::vector<unsigned char>),
            (EntityId, PlayerId, X,      Y,      Z,      YRot,          XRot,          RawMetadata)
        );
        DECLARE_SERIALIZE;
#else
        DECLARE_FIELDS(
            (VarInt,   UUID,     double, double, double, unsigned char, unsigned char),
            (EntityId, PlayerId, X,      Y,      Z,      YRot,          XRot)
        );
        DECLARE_READ_WRITE_SERIALIZE;
#endif

        GETTER_SETTER(EntityId);
        GETTER_SETTER(PlayerId);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
#if PROTOCOL_VERSION < 573 /* < 1.15 */
        GETTER_SETTER(RawMetadata);
#endif
    protected:
#if PROTOCOL_VERSION < 550 /* < 1.15 */
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetEntityId(ReadData<VarInt>(iter, length));
            SetPlayerId(ReadData<UUID>(iter, length));
            SetX(ReadData<double>(iter, length));
            SetY(ReadData<double>(iter, length));
            SetZ(ReadData<double>(iter, length));
            SetYRot(ReadData<unsigned char>(iter, length));
            SetXRot(ReadData<unsigned char>(iter, length));
            SetRawMetadata(ReadByteArray(iter, length, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetEntityId(), container);
            WriteData<UUID>(GetPlayerId(), container);
            WriteData<double>(GetX(), container);
            WriteData<double>(GetY(), container);
            WriteData<double>(GetZ(), container);
            WriteData<unsigned char>(GetYRot(), container);
            WriteData<unsigned char>(GetXRot(), container);
            WriteByteArray(GetRawMetadata(), container);
        }
#endif
    };
} //ProtocolCraft
#endif
