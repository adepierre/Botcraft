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
            SERIALIZED_FIELD(Rules, std::vector<ToolRule>);
            SERIALIZED_FIELD(DefaultMiningSpeed, float);
            SERIALIZED_FIELD(DamagePerBlock, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
