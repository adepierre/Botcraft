#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION < 393 /* < 1.13 */
#include "protocolCraft/Types/NetworkPosition.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundCommandSuggestionPacket : public BasePacket<ServerboundCommandSuggestionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Command Suggestion";

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
        SERIALIZED_FIELD(Id_, VarInt);
#endif
        SERIALIZED_FIELD(Command, std::string);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(AssumeCommand, bool);
        SERIALIZED_FIELD(LookedAtBlock, std::optional<NetworkPosition>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
