#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeItemContainerContents : public DataComponentType
        {
            SERIALIZED_FIELD(Items, std::vector<Slot>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
