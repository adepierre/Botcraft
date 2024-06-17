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
        DECLARE_FIELDS(
            (ChatMessageContent, long long int, long long int, std::vector<LastSeenMessagesEntry>),
            (Content,            Timestamp,     Salt,          LastSeen)
        );
#else
        DECLARE_FIELDS(
            (std::string, long long int, long long int, std::vector<LastSeenMessagesEntry>),
            (Content,     Timestamp,     Salt,          LastSeen)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Content);
        GETTER_SETTER(Timestamp);
        GETTER_SETTER(Salt);
        GETTER_SETTER(LastSeen);
    };
} // ProtocolCraft
#endif
