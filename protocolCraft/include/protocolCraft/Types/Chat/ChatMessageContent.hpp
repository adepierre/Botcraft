#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatMessageContent : public NetworkType
    {
        DECLARE_FIELDS(
            (std::string, std::optional<Chat>),
            (Plain,       Decorated)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Plain);
        GETTER_SETTER(Decorated);
    };
}
#endif
