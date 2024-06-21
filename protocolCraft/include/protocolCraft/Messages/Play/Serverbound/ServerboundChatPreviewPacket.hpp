#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChatPreviewPacket : public BaseMessage<ServerboundChatPreviewPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Chat Preview";

        DECLARE_FIELDS(
            (int,     std::string),
            (QueryId, Query)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(QueryId);
        GETTER_SETTER(Query);
    };
} //ProtocolCraft
#endif
