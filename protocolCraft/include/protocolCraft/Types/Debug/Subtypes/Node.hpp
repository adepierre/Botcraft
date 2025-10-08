#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Node : public NetworkType
    {
        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Y, int);
        SERIALIZED_FIELD(Z, int);
        SERIALIZED_FIELD(WalkedDistance, float);
        SERIALIZED_FIELD(CostMalus, float);
        SERIALIZED_FIELD(Closed, bool);
        SERIALIZED_FIELD(Type, VarInt);
        SERIALIZED_FIELD(F, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
