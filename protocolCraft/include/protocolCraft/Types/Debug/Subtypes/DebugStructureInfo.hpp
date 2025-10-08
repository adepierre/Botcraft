#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Debug/Subtypes/BoundingBox.hpp"
#include "protocolCraft/Types/Debug/Subtypes/DebugStructureInfoPiece.hpp"

#include <vector>

namespace ProtocolCraft
{
    class DebugStructureInfo : public NetworkType
    {
        SERIALIZED_FIELD(BoundingBox, ProtocolCraft::BoundingBox);
        SERIALIZED_FIELD(Pieces, std::vector<DebugStructureInfoPiece>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
