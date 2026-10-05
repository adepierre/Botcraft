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
#if PROTOCOL_VERSION > 776 /* > 26.2 */
            SERIALIZED_FIELD(DirectionalParticles, bool);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
