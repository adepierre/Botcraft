#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetDataPacket : public BasePacket<ClientboundContainerSetDataPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Set Data";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ContainerId, unsigned char);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
#endif
        SERIALIZED_FIELD(Id_, short);
        SERIALIZED_FIELD(Value, short);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
