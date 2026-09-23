#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityLinkPacket : public BasePacket<ClientboundSetEntityLinkPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Entity Link";

        SERIALIZED_FIELD(SourceId, int);
        SERIALIZED_FIELD(DestId, int);
#if PROTOCOL_VERSION < 107 /* < 1.9 */
        SERIALIZED_FIELD(Leash, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
