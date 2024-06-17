#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypePotDecorations : public DataComponentType
        {
            DECLARE_FIELDS(
                (std::vector<VarInt>),
                (Sides)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Sides);
        };
    }
}
#endif
