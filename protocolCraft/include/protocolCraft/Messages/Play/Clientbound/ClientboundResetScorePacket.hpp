#if PROTOCOL_VERSION > 764 /* > 1.20.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResetScorePacket : public BaseMessage<ClientboundResetScorePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Reset Score";

        SERIALIZED_FIELD(Owner, std::string);
        SERIALIZED_FIELD(ObjectiveName, std::optional<std::string>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
