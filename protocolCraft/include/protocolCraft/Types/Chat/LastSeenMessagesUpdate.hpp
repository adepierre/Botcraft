#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include <vector>

#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"
#endif

namespace ProtocolCraft
{
    class LastSeenMessagesUpdate : public NetworkType
    {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(LastSeen, std::vector<LastSeenMessagesEntry>);
        SERIALIZED_FIELD(LastReceived, std::optional<LastSeenMessagesEntry>);
#else
        SERIALIZED_FIELD(Offset, VarInt);
        SERIALIZED_FIELD(Acknowledged, std::bitset<20>);
#endif
        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
