#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffect.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeDeathProtection : public DataComponentType
        {
            SERIALIZED_FIELD(DeathEffects, std::vector<ConsumeEffect>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
