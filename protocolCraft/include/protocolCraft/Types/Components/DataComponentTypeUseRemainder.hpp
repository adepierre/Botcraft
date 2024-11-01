#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeUseRemainder : public DataComponentType
        {
            SERIALIZED_FIELD(ConvertInto, Slot);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
