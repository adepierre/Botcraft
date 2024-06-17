#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatTypeBoundNetwork : public NetworkType
    {
        DECLARE_FIELDS(
            (VarInt,   Chat, std::optional<Chat>),
            (ChatType, Name, TargetName)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ChatType);
        GETTER_SETTER(Name);
        GETTER_SETTER(TargetName);
    };
}
#endif
