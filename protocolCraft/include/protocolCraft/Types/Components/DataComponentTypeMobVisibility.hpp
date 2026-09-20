#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeMobVisibility: public DataComponentType
        {
            SERIALIZED_FIELD(TargetingEntityTypes, HolderSet);
            SERIALIZED_FIELD(Visibility, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
