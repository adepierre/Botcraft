#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityLinkPacket : public BaseMessage<ClientboundSetEntityLinkPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Entity Link";

        DECLARE_FIELDS(
            (int,      int),
            (SourceId, DestId)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(SourceId);
        GETTER_SETTER(DestId);
    };
} //ProtocolCraft
