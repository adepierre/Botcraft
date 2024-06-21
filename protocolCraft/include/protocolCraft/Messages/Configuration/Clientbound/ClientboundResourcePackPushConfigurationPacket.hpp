#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPushConfigurationPacket : public BaseMessage<ClientboundResourcePackPushConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Resource Pack Push (Configuration)";

        DECLARE_FIELDS(
            (UUID, std::string, std::string, bool,     std::optional<Chat>),
            (Uuid, Url,         Hash,        Required, Prompt)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
        GETTER_SETTER(Url);
        GETTER_SETTER(Hash);
        GETTER_SETTER(Required);
        GETTER_SETTER(Prompt);
    };
} //ProtocolCraft
#endif
