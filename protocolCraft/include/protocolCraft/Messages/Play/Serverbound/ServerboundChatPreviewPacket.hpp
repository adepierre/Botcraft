#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChatPreviewPacket : public BaseMessage<ServerboundChatPreviewPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x06;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat Preview";

        DECLARE_FIELDS_TYPES(int,     std::string);
        DECLARE_FIELDS_NAMES(QueryId, Query);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(QueryId);
        GETTER_SETTER(Query);
    };
} //ProtocolCraft
#endif
