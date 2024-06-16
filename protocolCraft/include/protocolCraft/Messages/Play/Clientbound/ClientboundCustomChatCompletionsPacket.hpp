#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomChatCompletionsPacket : public BaseMessage<ClientboundCustomChatCompletionsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x18;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Custom Chat Completion Packet";

        DECLARE_FIELDS_TYPES(VarInt, std::vector<std::string>);
        DECLARE_FIELDS_NAMES(Action, Entries);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Action);
        GETTER_SETTER(Entries);
    };
} //ProtocolCraft
#endif
