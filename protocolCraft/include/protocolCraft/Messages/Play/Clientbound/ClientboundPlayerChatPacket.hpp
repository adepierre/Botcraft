#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
#include "protocolCraft/Types/SaltSignature.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatSender.hpp"
#else
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Types/Chat/PlayerChatMessage.hpp"
#else
#include "protocolCraft/Types/Chat/SignedMessageBody.hpp"
#include "protocolCraft/Types/Chat/FilterMask.hpp"
#endif
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"
#endif


namespace ProtocolCraft
{
    class ClientboundPlayerChatPacket : public BaseMessage<ClientboundPlayerChatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x39;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Chat";

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS_TYPES(Chat,          std::optional<Chat>, VarInt, ChatSender, long long int, SaltSignature);
        DECLARE_FIELDS_NAMES(SignedContent, UnsignedContent,     TypeId, Sender,     Timestamp,     SaltSignature);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(PlayerChatMessage, ChatTypeBoundNetwork);
        DECLARE_FIELDS_NAMES(Message,           ChatType);
#else
        DECLARE_FIELDS_TYPES(UUID,   VarInt, std::optional<std::array<unsigned char, 256>>, SignedMessageBody, std::optional<Chat>, FilterMask, ChatTypeBoundNetwork);
        DECLARE_FIELDS_NAMES(Sender, Index,  Signature,                                     Body,              UnsignedContent,     FilterMask, ChatType);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        GETTER_SETTER(SignedContent);
        GETTER_SETTER(TypeId);
        GETTER_SETTER(Timestamp);
        GETTER_SETTER(SaltSignature);
#endif
#if PROTOCOL_VERSION == 761 /* 1.19.3 */
        GETTER_SETTER(Message);
        GETTER_SETTER(ChatType);
#else
        GETTER_SETTER(Sender);
        GETTER_SETTER(UnsignedContent);
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        GETTER_SETTER(Index);
        GETTER_SETTER(Signature);
        GETTER_SETTER(Body);
        GETTER_SETTER(FilterMask);
        GETTER_SETTER(ChatType);
#endif
    };
} //ProtocolCraft
#endif
