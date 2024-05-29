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
            DECLARE_FIELDS_TYPES(std::vector<Slot>);
            DECLARE_FIELDS_NAMES(Items);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Items);
        };
    }
}
#endif
