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
            (VarInt,   UUID,     double, double, double, unsigned char, unsigned char, Internal::Vector<unsigned char, void, 0>),
            (EntityId, PlayerId, X,      Y,      Z,      YRot,          XRot,          RawMetadata)
        );
#else
        DECLARE_FIELDS(
            (VarInt,   UUID,     double, double, double, unsigned char, unsigned char),
            (EntityId, PlayerId, X,      Y,      Z,      YRot,          XRot)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

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
    };
} //ProtocolCraft
#endif
