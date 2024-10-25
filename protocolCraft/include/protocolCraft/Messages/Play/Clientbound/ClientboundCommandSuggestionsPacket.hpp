#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundCommandSuggestionsPacket : public BaseMessage<ClientboundCommandSuggestionsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Command Suggestions";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(Suggestions, std::vector<std::string>);
#else
        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(Start, VarInt);
        SERIALIZED_FIELD(Length, VarInt);
        SERIALIZED_FIELD(Suggestions, std::map<std::string, std::optional<Chat>>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
