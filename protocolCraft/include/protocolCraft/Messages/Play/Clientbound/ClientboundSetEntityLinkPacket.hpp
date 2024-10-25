#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityLinkPacket : public BaseMessage<ClientboundSetEntityLinkPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Entity Link";

        SERIALIZED_FIELD(SourceId, int);
        SERIALIZED_FIELD(DestId, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
