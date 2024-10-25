#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatMessageContent : public NetworkType
    {
        SERIALIZED_FIELD(Plain, std::string);
        SERIALIZED_FIELD(Decorated, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
