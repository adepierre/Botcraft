#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffectData.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class TeleportRandomlyConsumeEffect : public ConsumeEffectData
        {
            SERIALIZED_FIELD(Diameter, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
