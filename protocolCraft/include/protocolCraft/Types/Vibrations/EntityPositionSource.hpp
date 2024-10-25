#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Vibrations/PositionSource.hpp"

namespace ProtocolCraft
{
    class EntityPositionSource : public PositionSource
    {
        SERIALIZED_FIELD(SourceEntityId, VarInt);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(YOffset, float);
#endif
        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
