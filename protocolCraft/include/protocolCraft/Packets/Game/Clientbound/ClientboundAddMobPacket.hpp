#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundAddMobPacket : public BasePacket<ClientboundAddMobPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Mob";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Uuid, UUID);
        SERIALIZED_FIELD(Type, VarInt);
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(YRot, unsigned char);
        SERIALIZED_FIELD(XRot, unsigned char);
        SERIALIZED_FIELD(YHeadRot, unsigned char);
        SERIALIZED_FIELD(Xd, short);
        SERIALIZED_FIELD(Yd, short);
        SERIALIZED_FIELD(Zd, short);
#if PROTOCOL_VERSION < 573 /* < 1.15 */
        SERIALIZED_FIELD(RawMetadata, Internal::Vector<unsigned char, void, 0>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
