#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSwingAnimationPacket : public BasePacket<ClientboundSwingAnimationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Swing Animation";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Hand, VarInt);
        SERIALIZED_FIELD(Animation, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
