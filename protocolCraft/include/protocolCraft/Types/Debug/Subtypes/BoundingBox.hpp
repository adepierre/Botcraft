#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class BoundingBox : public NetworkType
    {
        SERIALIZED_FIELD(Min, NetworkPosition);
        SERIALIZED_FIELD(Max, NetworkPosition);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
