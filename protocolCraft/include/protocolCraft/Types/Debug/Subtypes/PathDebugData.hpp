#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Debug/Subtypes/Node.hpp"

#include <vector>

namespace ProtocolCraft
{
    class PathDebugData : public NetworkType
    {
        SERIALIZED_FIELD(OpenSet, std::vector<Node>);
        SERIALIZED_FIELD(ClosedSet, std::vector<Node>);
        SERIALIZED_FIELD(TargetNodes, std::vector<Node>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
