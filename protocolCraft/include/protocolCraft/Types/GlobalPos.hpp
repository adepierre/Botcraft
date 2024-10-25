#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class GlobalPos : public NetworkType
    {
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Pos, NetworkPosition);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
