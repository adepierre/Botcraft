#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeRepairable : public DataComponentType
        {
            SERIALIZED_FIELD(Items, HolderSet);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
