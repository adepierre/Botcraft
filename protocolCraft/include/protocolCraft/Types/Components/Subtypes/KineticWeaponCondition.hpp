#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class KineticWeaponCondition : public NetworkType
        {
            SERIALIZED_FIELD(MaxDurationTicks, VarInt);
            SERIALIZED_FIELD(MinSpeed, float);
            SERIALIZED_FIELD(MinRelativeSpeed, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
