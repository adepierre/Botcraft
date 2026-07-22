#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/DataComponents.hpp"
#include "protocolCraft/Types/Components/Subtypes/PartialDataComponentPredicate.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentMatchers : public NetworkType
        {
            SERIALIZED_FIELD(Exact, DataComponentPredicate);
            SERIALIZED_FIELD(Partial, std::vector<PartialDataComponentPredicate>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
