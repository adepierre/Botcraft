#if PROTOCOL_VERSION > 764 /* > 1.20.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResetScorePacket : public BaseMessage<ClientboundResetScorePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Reset Score";

        DECLARE_FIELDS(
            (std::string, std::optional<std::string>),
            (Owner,       ObjectiveName)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Owner);
        GETTER_SETTER(ObjectiveName);
    };
} //ProtocolCraft
#endif
