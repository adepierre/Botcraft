#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundSetActionBarTextPacket : public BasePacket<ClientboundSetActionBarTextPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Action Bar Text";

        SERIALIZED_FIELD(Text, Chat);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
