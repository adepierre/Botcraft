#if PROTOCOL_VERSION > 766 /* > 1.20.5 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/ChatTypeDecoration.hpp"

namespace ProtocolCraft
{
    class DirectChatType : public NetworkType
    {
        SERIALIZED_FIELD(Chat, ChatTypeDecoration);
        SERIALIZED_FIELD(Narration, ChatTypeDecoration);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
