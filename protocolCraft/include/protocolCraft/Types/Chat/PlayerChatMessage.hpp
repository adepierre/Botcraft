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
        SERIALIZED_FIELD(SignedHeader, SignedMessageHeader);
        SERIALIZED_FIELD(HeaderSignature, std::vector<unsigned char>);
        SERIALIZED_FIELD(SignedBody, SignedMessageBody);
        SERIALIZED_FIELD(UnsignedContent, std::optional<Chat>);
        SERIALIZED_FIELD(FilterMask, ProtocolCraft::FilterMask);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
