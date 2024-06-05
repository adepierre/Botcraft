#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundSystemChatPacket : public BaseMessage<ClientboundSystemChatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x62;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x60;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x64;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x69;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x6C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "System Chat";

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS_TYPES(Chat,    VarInt);
        DECLARE_FIELDS_NAMES(Content, TypeId);
#else
        DECLARE_FIELDS_TYPES(Chat,    bool);
        DECLARE_FIELDS_NAMES(Content, Overlay);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Content);
#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        GETTER_SETTER(TypeId);
#else
        GETTER_SETTER(Overlay);
#endif
    };
} //ProtocolCraft
#endif
