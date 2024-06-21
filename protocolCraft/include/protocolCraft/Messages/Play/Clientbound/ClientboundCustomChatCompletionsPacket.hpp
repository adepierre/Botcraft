#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomChatCompletionsPacket : public BaseMessage<ClientboundCustomChatCompletionsPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Custom Chat Completion Packet";

        DECLARE_FIELDS(
            (VarInt, std::vector<std::string>),
            (Action, Entries)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Action);
        GETTER_SETTER(Entries);
    };
} //ProtocolCraft
#endif
