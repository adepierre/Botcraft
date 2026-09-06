#if PROTOCOL_VERSION < 110 /* < 1.9.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateSignPacket : public BasePacket<ClientboundUpdateSignPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Sign";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(Line1, Chat);
        SERIALIZED_FIELD(Line2, Chat);
        SERIALIZED_FIELD(Line3, Chat);
        SERIALIZED_FIELD(Line4, Chat);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
