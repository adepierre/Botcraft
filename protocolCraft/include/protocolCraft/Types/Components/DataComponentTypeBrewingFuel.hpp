#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/ResolvableInt.hpp"
#include "protocolCraft/Types/Components/Subtypes/ResolvableFloat.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBrewingFuel : public DataComponentType
        {
            SERIALIZED_FIELD(Uses, ResolvableInt);
            SERIALIZED_FIELD(SpeedMultiplier, ResolvableFloat);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
