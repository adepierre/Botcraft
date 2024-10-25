#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/BlockPredicate.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeAdventureModePredicate : public DataComponentType
        {
            SERIALIZED_FIELD(Predicates, std::vector<BlockPredicate>);
            SERIALIZED_FIELD(ShowInTooltip, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
