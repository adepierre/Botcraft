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
        DECLARE_FIELDS(
            (std::vector<std::string>),
            (Suggestions)
        );
#else
        DECLARE_FIELDS(
            (VarInt, VarInt, VarInt, std::map<std::string, std::optional<Chat>>),
            (Id_,    Start,  Length, Suggestions)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Suggestions);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        GETTER_SETTER(Id_);
        GETTER_SETTER(Start);
        GETTER_SETTER(Length);
#endif
    };
} //ProtocolCraft
