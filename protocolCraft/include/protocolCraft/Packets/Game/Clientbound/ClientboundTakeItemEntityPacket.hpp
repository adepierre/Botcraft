#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundTakeItemEntityPacket : public BasePacket<ClientboundTakeItemEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Take Item Entity";

        SERIALIZED_FIELD(ItemId, VarInt);
        SERIALIZED_FIELD(PlayerId, VarInt);
#if PROTOCOL_VERSION > 210 /* > 1.10.2 */
        SERIALIZED_FIELD(Amount, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
