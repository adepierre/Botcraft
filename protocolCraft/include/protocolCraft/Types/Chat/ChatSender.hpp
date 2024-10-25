#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatSender : public NetworkType
    {
        SERIALIZED_FIELD(Uuid, UUID);
        SERIALIZED_FIELD(Name, Chat);
        SERIALIZED_FIELD(TeamName, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
