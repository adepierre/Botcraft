#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/ResolvableInt.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeCompostable : public DataComponentType
        {
            SERIALIZED_FIELD(Layers, ResolvableInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
