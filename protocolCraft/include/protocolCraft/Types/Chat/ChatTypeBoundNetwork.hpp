#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

#if PROTOCOL_VERSION > 766 /* > 1.20.5 */
#include "protocolCraft/Types/Chat/DirectChatType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#endif

namespace ProtocolCraft
{
    class ChatTypeBoundNetwork : public NetworkType
    {
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        SERIALIZED_FIELD(ChatType, VarInt);
#else
        SERIALIZED_FIELD(ChatType, Holder<DirectChatType>);
#endif
        SERIALIZED_FIELD(Name, Chat);
        SERIALIZED_FIELD(TargetName, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
