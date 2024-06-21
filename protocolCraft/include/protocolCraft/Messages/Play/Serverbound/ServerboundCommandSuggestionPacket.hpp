#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION < 393 /* < 1.13 */
#include "protocolCraft/Types/NetworkPosition.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundCommandSuggestionPacket : public BaseMessage<ServerboundCommandSuggestionPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Command Suggestion";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (std::string, bool,          std::optional<NetworkPosition>),
            (Command,     AssumeCommand, LookedAtBlock)
        );
#else
        DECLARE_FIELDS(
            (VarInt, std::string),
            (Id_,    Command)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Command);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        GETTER_SETTER(AssumeCommand);
        GETTER_SETTER(LookedAtBlock);
#endif
#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
        GETTER_SETTER(Id_);
#endif
    };
} //ProtocolCraft
