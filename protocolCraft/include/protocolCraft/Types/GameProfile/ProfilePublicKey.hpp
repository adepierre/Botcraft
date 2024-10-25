#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ProfilePublicKey : public NetworkType
    {
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(Key, std::vector<unsigned char>);
        SERIALIZED_FIELD(Signature, std::vector<unsigned char>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
