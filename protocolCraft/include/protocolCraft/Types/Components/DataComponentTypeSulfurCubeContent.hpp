#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Item/ItemStackTemplate.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeSulfurCubeContent : public DataComponentType
        {
            SERIALIZED_FIELD(AbsorbedBlockItemStack, ItemStackTemplate);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
