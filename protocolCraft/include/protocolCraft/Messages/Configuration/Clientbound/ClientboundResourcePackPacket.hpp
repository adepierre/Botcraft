#if PROTOCOL_VERSION > 763 /* > 1.20.1 */ && PROTOCOL_VERSION < 765 /* < 1.20.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackConfigurationPacket : public BaseMessage<ClientboundResourcePackConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Resource Pack (Configuration)";

        DECLARE_FIELDS(
            (std::string, std::string, bool,     std::optional<Chat>),
            (Url,         Hash,        Required, Prompt)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Url);
        GETTER_SETTER(Hash);
        GETTER_SETTER(Required);
        GETTER_SETTER(Prompt);
    };
} //ProtocolCraft
#endif
