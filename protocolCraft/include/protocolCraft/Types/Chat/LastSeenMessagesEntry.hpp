#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#endif

namespace ProtocolCraft
{
    class LastSeenMessagesEntry : public NetworkType
    {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(ProfileId, UUID);
        SERIALIZED_FIELD(LastSignature, std::vector<unsigned char>);
#else
        SERIALIZED_FIELD(LastSignature, Holder<std::array<unsigned char, 256>>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
