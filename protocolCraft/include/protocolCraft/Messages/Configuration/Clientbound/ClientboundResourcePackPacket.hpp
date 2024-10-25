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

        SERIALIZED_FIELD(Url, std::string);
        SERIALIZED_FIELD(Hash, std::string);
        SERIALIZED_FIELD(Required, bool);
        SERIALIZED_FIELD(Prompt, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
