#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 756 /* < 1.17.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveEntityPacket : public BasePacket<ClientboundRemoveEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Remove Entity";

        SERIALIZED_FIELD(EntityId, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
