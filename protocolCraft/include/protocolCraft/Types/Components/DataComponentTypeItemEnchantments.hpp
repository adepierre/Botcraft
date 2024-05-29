#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include <map>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeItemEnchantments : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(std::map<VarInt, VarInt>, bool);
            DECLARE_FIELDS_NAMES(Enchantments,             ShowInTooltip);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Enchantments);
            GETTER_SETTER(ShowInTooltip);
        };
    }
}
#endif
