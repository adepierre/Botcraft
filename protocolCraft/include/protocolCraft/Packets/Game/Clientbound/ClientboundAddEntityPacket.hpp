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

#if PROTOCOL_VERSION < 107 /* < 1.9 */
        DEFINE_CONDITION(HasSpeed, GetData() > 0);
#endif

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION > 47 /* > 1.8.9 */
        SERIALIZED_FIELD(Uuid, UUID);
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        SERIALIZED_FIELD(Type, char);
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
#if PROTOCOL_VERSION < 107 /* < 1.9 */
        SERIALIZED_FIELD(Xa, Internal::Conditioned<short, &THIS::HasSpeed>);
        SERIALIZED_FIELD(Ya, Internal::Conditioned<short, &THIS::HasSpeed>);
        SERIALIZED_FIELD(Za, Internal::Conditioned<short, &THIS::HasSpeed>);
#elif PROTOCOL_VERSION < 773 /* < 1.21.9 */
        SERIALIZED_FIELD(Xa, short);
        SERIALIZED_FIELD(Ya, short);
        SERIALIZED_FIELD(Za, short);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
