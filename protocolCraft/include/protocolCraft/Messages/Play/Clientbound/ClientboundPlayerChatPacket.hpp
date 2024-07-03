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

        static constexpr std::string_view packet_name = "Player Chat";

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS(
            (Chat,          std::optional<Chat>, VarInt, ChatSender, long long int, SaltSignature),
            (SignedContent, UnsignedContent,     TypeId, Sender,     Timestamp,     SaltSignature)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (PlayerChatMessage, ChatTypeBoundNetwork),
            (Message_,          ChatType)
        );
#else
        DECLARE_FIELDS(
            (UUID,   VarInt, std::optional<std::array<unsigned char, 256>>, SignedMessageBody, std::optional<Chat>, FilterMask, ChatTypeBoundNetwork),
            (Sender, Index,  Signature,                                     Body,              UnsignedContent,     FilterMask, ChatType)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        GETTER_SETTER(SignedContent);
        GETTER_SETTER(TypeId);
        GETTER_SETTER(Timestamp);
        GETTER_SETTER(SaltSignature);
#endif
#if PROTOCOL_VERSION == 760 /* 1.19.2 */
        GETTER_SETTER(Message_);
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
