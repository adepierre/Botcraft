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
        SERIALIZED_FIELD(SignedContent, Chat);
        SERIALIZED_FIELD(UnsignedContent, std::optional<Chat>);
        SERIALIZED_FIELD(TypeId, VarInt);
        SERIALIZED_FIELD(Sender, ChatSender);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(SaltSignature, ProtocolCraft::SaltSignature);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Message_, PlayerChatMessage);
        SERIALIZED_FIELD(ChatType, ChatTypeBoundNetwork);
#else
        SERIALIZED_FIELD(Sender, UUID);
        SERIALIZED_FIELD(Index, VarInt);
        SERIALIZED_FIELD(Signature, std::optional<std::array<unsigned char, 256>>);
        SERIALIZED_FIELD(Body, SignedMessageBody);
        SERIALIZED_FIELD(UnsignedContent, std::optional<Chat>);
        SERIALIZED_FIELD(FilterMask, ProtocolCraft::FilterMask);
        SERIALIZED_FIELD(ChatType, ChatTypeBoundNetwork);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
