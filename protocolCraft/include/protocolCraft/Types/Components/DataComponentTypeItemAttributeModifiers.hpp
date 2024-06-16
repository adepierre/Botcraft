#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiersEntry.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeItemAttributeModifiers : public DataComponentType
        {
            DECLARE_FIELDS(
                (std::vector<ItemAttributeModifiersEntry>, bool),
                (Modifiers,                                ShowInTooltip)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Modifiers);
            GETTER_SETTER(ShowInTooltip);
        };
    }
}
#endif
