#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 772 /* > 1.21.9 */
#include "protocolCraft/Types/LpVec3.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetEntityMotionPacket : public BasePacket<ClientboundSetEntityMotionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Entity Motion";

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
        SERIALIZED_FIELD(XA, short);
        SERIALIZED_FIELD(YA, short);
        SERIALIZED_FIELD(ZA, short);
#else
        SERIALIZED_FIELD(Movement, LpVec3);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
