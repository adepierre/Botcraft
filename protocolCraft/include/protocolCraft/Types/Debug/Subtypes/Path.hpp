#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

#include "protocolCraft/Types/Debug/Subtypes/Node.hpp"
#include "protocolCraft/Types/Debug/Subtypes/PathDebugData.hpp"

namespace ProtocolCraft
{
    class Path : public NetworkType
    {
        SERIALIZED_FIELD(Reached, bool);
        SERIALIZED_FIELD(NextNodeIndex, int);
        SERIALIZED_FIELD(Target, NetworkPosition);
        SERIALIZED_FIELD(Nodes, std::vector<Node>);
        SERIALIZED_FIELD(DebugData, PathDebugData);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
