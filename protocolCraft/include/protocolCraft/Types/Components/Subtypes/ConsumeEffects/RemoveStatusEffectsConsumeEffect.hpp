#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffectData.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class RemoveStatusEffectsConsumeEffect : public ConsumeEffectData
        {
            SERIALIZED_FIELD(Effects, HolderSet);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
