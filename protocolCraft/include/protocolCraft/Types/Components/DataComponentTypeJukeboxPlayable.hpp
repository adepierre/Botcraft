#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeJukeboxPlayable : public DataComponentType
        {
            SERIALIZED_FIELD(Material, VarInt);
            SERIALIZED_FIELD(Pattern, VarInt);
            SERIALIZED_FIELD(ShowInTooltip, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
