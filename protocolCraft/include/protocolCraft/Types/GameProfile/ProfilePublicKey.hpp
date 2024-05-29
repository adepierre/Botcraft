#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ProfilePublicKey : public NetworkType
    {
        DECLARE_FIELDS_TYPES(long long int, std::vector<unsigned char>, std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(Timestamp,     Key,                        Signature);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Timestamp);
        GETTER_SETTER(Key);
        GETTER_SETTER(Signature);
    };
} // ProtocolCraft
#endif
