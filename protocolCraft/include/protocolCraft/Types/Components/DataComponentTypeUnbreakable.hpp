#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeUnbreakable : public DataComponentType
        {
            SERIALIZED_FIELD(ShowInTooltip, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
