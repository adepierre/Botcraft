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
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            SERIALIZED_FIELD(CanDestroyBlocksInCreative, bool);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
