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

        SERIALIZED_FIELD(QueryId, int);
        SERIALIZED_FIELD(Query, std::string);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
