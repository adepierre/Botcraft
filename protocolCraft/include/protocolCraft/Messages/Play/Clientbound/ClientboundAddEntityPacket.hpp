#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddEntityPacket : public BaseMessage<ClientboundAddEntityPacket>
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
        SERIALIZED_FIELD(Xa, short);
        SERIALIZED_FIELD(Ya, short);
        SERIALIZED_FIELD(Za, short);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
