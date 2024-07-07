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
        DECLARE_FIELDS(
            (UUID,      std::vector<unsigned char>),
            (ProfileId, LastSignature)
        );
#else
        DECLARE_FIELDS(
            (Holder<std::array<unsigned char, 256>>),
            (LastSignature)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;


#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(ProfileId);
#endif
        GETTER_SETTER(LastSignature);
    };
} // ProtocolCraft
#endif
