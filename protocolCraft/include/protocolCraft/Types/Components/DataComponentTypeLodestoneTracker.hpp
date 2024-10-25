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
            SERIALIZED_FIELD(Target, std::optional<GlobalPos>);
            SERIALIZED_FIELD(Tracked, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
