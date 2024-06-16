#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeChargedProjectiles : public DataComponentType
        {
            DECLARE_FIELDS(
                (std::vector<Slot>),
                (List)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(List);
        };
    }
}
#endif
