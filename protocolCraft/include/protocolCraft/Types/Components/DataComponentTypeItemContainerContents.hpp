#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#if PROTOCOL_VERSION < 775 /* < 26.1 */
#include "protocolCraft/Types/Item/Slot.hpp"
#else
#include "protocolCraft/Types/Item/ItemStackTemplate.hpp"

#include <optional>
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeItemContainerContents : public DataComponentType
        {
#if PROTOCOL_VERSION < 775 /* < 26.1 */
            SERIALIZED_FIELD(Items, std::vector<Slot>);
#else
            SERIALIZED_FIELD(Items, std::vector<std::optional<ItemStackTemplate>>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
