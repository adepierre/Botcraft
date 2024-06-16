#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/GlobalPos.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeLodestoneTracker : public DataComponentType
        {
            DECLARE_FIELDS(
                (std::optional<GlobalPos>, bool),
                (Target,                   Tracked)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Target);
            GETTER_SETTER(Tracked);
        };
    }
}
#endif
