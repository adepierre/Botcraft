#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Types/Chat/ChatMessageContent.hpp"
#endif
#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"

namespace ProtocolCraft
{
    class SignedMessageBody : public NetworkType
    {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Content, ChatMessageContent);
#else
        SERIALIZED_FIELD(Content, std::string);
#endif
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(Salt, long long int);
        SERIALIZED_FIELD(LastSeen, std::vector<LastSeenMessagesEntry>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
