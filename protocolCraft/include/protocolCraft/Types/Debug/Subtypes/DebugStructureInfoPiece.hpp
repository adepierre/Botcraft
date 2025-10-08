#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Debug/Subtypes/BoundingBox.hpp"

namespace ProtocolCraft
{
    class DebugStructureInfoPiece : public NetworkType
    {
        SERIALIZED_FIELD(BoundingBox, ProtocolCraft::BoundingBox);
        SERIALIZED_FIELD(IsStart, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
