#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#if PROTOCOL_VERSION < 775 /* < 26.1 */
#include "protocolCraft/Types/Item/Slot.hpp"
#else
#include "protocolCraft/Types/Item/ItemStackTemplate.hpp"
#endif

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeChargedProjectiles : public DataComponentType
        {
#if PROTOCOL_VERSION < 775 /* < 26.1 */
            SERIALIZED_FIELD(List, std::vector<Slot>);
#else
            SERIALIZED_FIELD(List, std::vector<ItemStackTemplate>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
