#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ChunkPos : public NetworkType
    {
        SERIALIZED_FIELD(Z, int);
        SERIALIZED_FIELD(X, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
