#if PROTOCOL_VERSION > 764 /* > 1.20.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResetScorePacket : public BaseMessage<ClientboundResetScorePacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x44;
#else
#error "Protocol version not implemented"
#endif

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
