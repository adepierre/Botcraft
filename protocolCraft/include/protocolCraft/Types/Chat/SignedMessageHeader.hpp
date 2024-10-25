#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class SignedMessageHeader : public NetworkType
    {
        SERIALIZED_FIELD(PreviousSignature, std::optional<std::vector<unsigned char>>);
        SERIALIZED_FIELD(Sender, UUID);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
