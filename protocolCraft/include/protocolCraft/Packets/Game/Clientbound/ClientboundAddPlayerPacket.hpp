#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPlayerPacket : public BasePacket<ClientboundAddPlayerPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Player";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(PlayerId, UUID);
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(YRot, unsigned char);
        SERIALIZED_FIELD(XRot, unsigned char);
#if PROTOCOL_VERSION < 573 /* < 1.15 */
        SERIALIZED_FIELD(RawMetadata, Internal::Vector<unsigned char, void, 0>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
