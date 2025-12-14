#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeUseEffects : public DataComponentType
        {
            SERIALIZED_FIELD(CanSprint, bool);
            SERIALIZED_FIELD(InteractVibration, bool);
            SERIALIZED_FIELD(SpeedMultiplier, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
