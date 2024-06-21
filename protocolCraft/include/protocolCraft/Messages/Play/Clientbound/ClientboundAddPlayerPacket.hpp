#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPlayerPacket : public BaseMessage<ClientboundAddPlayerPacket>
    {
    public:

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
