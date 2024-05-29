#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/FilterMask.hpp"
#include "protocolCraft/Types/Chat/SignedMessageHeader.hpp"
#include "protocolCraft/Types/Chat/SignedMessageBody.hpp"

namespace ProtocolCraft
{
    class PlayerChatMessage : public NetworkType
    {
        DECLARE_FIELDS_TYPES(SignedMessageHeader, std::vector<unsigned char>, SignedMessageBody, std::optional<Chat>, FilterMask);
        DECLARE_FIELDS_NAMES(SignedHeader,        HeaderSignature,            SignedBody,        UnsignedContent,     FilterMask);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(SignedHeader);
        GETTER_SETTER(HeaderSignature);
        GETTER_SETTER(SignedBody);
        GETTER_SETTER(UnsignedContent);
        GETTER_SETTER(FilterMask);
    };
}
#endif
