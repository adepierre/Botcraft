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
        DECLARE_FIELDS_TYPES(std::vector<LastSeenMessagesEntry>, std::optional<LastSeenMessagesEntry>);
        DECLARE_FIELDS_NAMES(LastSeen,                           LastReceived);
#else
        DECLARE_FIELDS_TYPES(VarInt, std::bitset<20>);
        DECLARE_FIELDS_NAMES(Offset, Acknowledged);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(LastSeen);
        GETTER_SETTER(LastReceived);
#else
        GETTER_SETTER(Offset);
        GETTER_SETTER(Acknowledged);
#endif
    };
} // ProtocolCraft
#endif
