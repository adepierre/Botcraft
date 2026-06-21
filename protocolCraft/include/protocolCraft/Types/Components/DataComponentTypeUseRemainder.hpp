#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#if PROTOCOL_VERSION < 775 /* < 26.1 */
#include "protocolCraft/Types/Item/Slot.hpp"
#else
#include "protocolCraft/Types/Item/ItemStackTemplate.hpp"
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeUseRemainder : public DataComponentType
        {
#if PROTOCOL_VERSION < 775 /* < 26.1 */
            SERIALIZED_FIELD(ConvertInto, Slot);
#else
            SERIALIZED_FIELD(ConvertInto, ItemStackTemplate);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
