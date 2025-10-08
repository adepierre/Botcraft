#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/GlobalPos.hpp"

namespace ProtocolCraft
{
    class LevelDataRespawnData : public NetworkType
    {
        SERIALIZED_FIELD(GlobalPos, ProtocolCraft::GlobalPos);
        SERIALIZED_FIELD(Yaw, float);
        SERIALIZED_FIELD(Pitch, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
