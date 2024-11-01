#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffectData.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class ClearAllStatusEffectsConsumeEffect : public ConsumeEffectData
        {
            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
