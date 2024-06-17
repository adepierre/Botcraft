#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class SignedMessageHeader : public NetworkType
    {
        DECLARE_FIELDS(
            (std::optional<std::vector<unsigned char>>, UUID),
            (PreviousSignature,                         Sender)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(PreviousSignature);
        GETTER_SETTER(Sender);
    };
} // ProtocolCraft
#endif
