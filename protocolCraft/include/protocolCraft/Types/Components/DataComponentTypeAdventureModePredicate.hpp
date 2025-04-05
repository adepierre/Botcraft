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
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            SERIALIZED_FIELD(ShowInTooltip, bool);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
