#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/SuspiciousStewEntry.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeSuspiciousStewEffects : public DataComponentType
        {
            SERIALIZED_FIELD(Effects, std::vector<SuspiciousStewEntry>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
