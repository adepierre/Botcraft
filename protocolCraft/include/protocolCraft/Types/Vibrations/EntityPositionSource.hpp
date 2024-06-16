#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Vibrations/PositionSource.hpp"

namespace ProtocolCraft
{
    class EntityPositionSource : public PositionSource
    {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt),
            (SourceEntityId)
        );
#else
        DECLARE_FIELDS(
            (VarInt,         float),
            (SourceEntityId, YOffset)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(SourceEntityId);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(YOffset);
#endif
    };
}
#endif
