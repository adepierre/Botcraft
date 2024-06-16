#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/ToolRule.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeTool : public DataComponentType
        {
            DECLARE_FIELDS(
                (std::vector<ToolRule>, float,              VarInt),
                (Rules,                 DefaultMiningSpeed, DamagePerBlock)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Rules);
            GETTER_SETTER(DefaultMiningSpeed);
            GETTER_SETTER(DamagePerBlock);
        };
    }
}
#endif
