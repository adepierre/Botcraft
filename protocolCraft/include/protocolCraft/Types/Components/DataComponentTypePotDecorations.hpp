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
            SERIALIZED_FIELD(Sides, std::vector<VarInt>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
