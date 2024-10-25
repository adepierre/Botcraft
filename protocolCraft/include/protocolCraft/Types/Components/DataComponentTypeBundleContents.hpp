#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBundleContents : public DataComponentType
        {
            SERIALIZED_FIELD(List, std::vector<Slot>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
