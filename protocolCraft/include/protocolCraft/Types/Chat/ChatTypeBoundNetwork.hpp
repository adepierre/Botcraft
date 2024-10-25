#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatTypeBoundNetwork : public NetworkType
    {
        SERIALIZED_FIELD(ChatType, VarInt);
        SERIALIZED_FIELD(Name, Chat);
        SERIALIZED_FIELD(TargetName, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
