#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPacket : public BaseMessage<ClientboundChatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (Chat,    char),
            (Message, Type)
        );
#else
        DECLARE_FIELDS(
            (Chat,    char, UUID),
            (Message, Type, Sender)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Message);
        GETTER_SETTER(Type);
#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
        GETTER_SETTER(Sender);
#endif
    };
} //ProtocolCraft
#endif
