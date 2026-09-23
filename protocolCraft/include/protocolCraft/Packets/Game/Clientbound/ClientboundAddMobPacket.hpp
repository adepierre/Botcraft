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
#if PROTOCOL_VERSION > 47 /* > 1.8.9 */
        SERIALIZED_FIELD(Uuid, UUID);
#endif
#if PROTOCOL_VERSION < 315 /* < 1.11 */
        SERIALIZED_FIELD(Type, unsigned char);
#else
        SERIALIZED_FIELD(Type, VarInt);
#endif
#if PROTOCOL_VERSION < 107 /* < 1.9 */
        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Y, int);
        SERIALIZED_FIELD(Z, int);
#else
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
#endif
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
