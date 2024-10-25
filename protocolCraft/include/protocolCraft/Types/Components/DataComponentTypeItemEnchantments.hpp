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
            SERIALIZED_FIELD(Enchantments, std::map<VarInt, VarInt>);
            SERIALIZED_FIELD(ShowInTooltip, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
