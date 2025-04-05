#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/DataComponents.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeTooltipDisplay : public DataComponentType
        {
            SERIALIZED_FIELD(HideTooltip, bool);
            SERIALIZED_FIELD(HiddenComponents, Internal::DiffType<std::vector<DataComponentTypes>, std::vector<VarInt>>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
