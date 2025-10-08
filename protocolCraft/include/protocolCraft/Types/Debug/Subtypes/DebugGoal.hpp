#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class DebugGoal : public NetworkType
    {
        SERIALIZED_FIELD(Priority, VarInt);
        SERIALIZED_FIELD(IsRunning, bool);
        SERIALIZED_FIELD(name, std::string);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
