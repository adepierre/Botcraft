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
            DECLARE_FIELDS(
                (std::vector<BlockPredicate>, bool),
                (Predicates, ShowInTooltip)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Predicates);
            GETTER_SETTER(ShowInTooltip);
        };
    }
}
#endif
