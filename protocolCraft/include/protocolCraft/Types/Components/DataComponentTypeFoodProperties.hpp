#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/PossibleEffect.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeFoodProperties : public DataComponentType
        {
            SERIALIZED_FIELD(Nutrition, VarInt);
            SERIALIZED_FIELD(Saturation, float);
            SERIALIZED_FIELD(CanAlwaysEat, bool);
            SERIALIZED_FIELD(EatSeconds, float);
            SERIALIZED_FIELD(Effects, std::vector<PossibleEffect>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
