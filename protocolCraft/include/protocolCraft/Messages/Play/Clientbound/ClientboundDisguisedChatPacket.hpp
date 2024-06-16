#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"

namespace ProtocolCraft
{
    class ClientboundDisguisedChatPacket : public BaseMessage<ClientboundDisguisedChatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x1E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Disguised Chat";

        DECLARE_FIELDS(
            (Chat, ChatTypeBoundNetwork),
            (Message, ChatType)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Message);
        GETTER_SETTER(ChatType);
    };
} //ProtocolCraft
#endif
