#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomChatCompletionsPacket : public BaseMessage<ClientboundCustomChatCompletionsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Chat Completion Packet";

        SERIALIZED_FIELD(Action, VarInt);
        SERIALIZED_FIELD(Entries, std::vector<std::string>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
