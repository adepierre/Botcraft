#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Components/Subtypes/PaintingVariant.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypePaintingVariant : public DataComponentType
        {
            SERIALIZED_FIELD(Variant, Holder<PaintingVariant>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
