#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/LpVec3.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundAddEntityPacket : public BasePacket<ClientboundAddEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Entity";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Uuid, UUID);
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        SERIALIZED_FIELD(Type, char);
#else
        SERIALIZED_FIELD(Type, VarInt);
#endif
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        SERIALIZED_FIELD(Movement, LpVec3);
#endif
        SERIALIZED_FIELD(XRot, unsigned char);
        SERIALIZED_FIELD(YRot, unsigned char);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(YHeadRot, unsigned char);
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(Data, int);
#else
        SERIALIZED_FIELD(Data, VarInt);
#endif
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
        SERIALIZED_FIELD(Xa, short);
        SERIALIZED_FIELD(Ya, short);
        SERIALIZED_FIELD(Za, short);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
