#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <vector>

namespace ProtocolCraft
{
    class SaltSignature : public NetworkType
    {
        SERIALIZED_FIELD(Salt, long long int);
        SERIALIZED_FIELD(Signature, std::vector<unsigned char>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
