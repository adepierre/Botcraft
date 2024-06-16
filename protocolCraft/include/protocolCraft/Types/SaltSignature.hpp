#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class SaltSignature : public NetworkType
    {
        DECLARE_FIELDS(
            (long long int, std::vector<unsigned char>),
            (Salt,          Signature)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Salt);
        GETTER_SETTER(Signature);
    };
} // ProtocolCraft
#endif
