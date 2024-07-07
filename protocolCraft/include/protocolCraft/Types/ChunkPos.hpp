#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ChunkPos : public NetworkType
    {
        DECLARE_FIELDS(
            (int, int),
            (Z,   X)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Z);
    };
}
#endif
