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
            DECLARE_FIELDS(
                (std::map<VarInt, VarInt>, bool),
                (Enchantments,             ShowInTooltip)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Enchantments);
            GETTER_SETTER(ShowInTooltip);
        };
    }
}
#endif
