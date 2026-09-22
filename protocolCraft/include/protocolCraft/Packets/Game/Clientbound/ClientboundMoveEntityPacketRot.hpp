#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketRot : public BasePacket<ClientboundMoveEntityPacketRot>
    {
    public:
        static constexpr std::string_view packet_name = "Move Entity Rot";

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION > 776 /* > 26.2 */
        SERIALIZED_FIELD(OnGround, bool);
#endif
        SERIALIZED_FIELD(YRot, unsigned char);
        SERIALIZED_FIELD(XRot, unsigned char);
#if PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(OnGround, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
