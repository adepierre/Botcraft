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
            DECLARE_FIELDS(
                (VarInt,    float,      bool,         float,      std::vector<PossibleEffect>),
                (Nutrition, Saturation, CanAlwaysEat, EatSeconds, Effects)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Nutrition);
            GETTER_SETTER(Saturation);
            GETTER_SETTER(CanAlwaysEat);
            GETTER_SETTER(EatSeconds);
            GETTER_SETTER(Effects);
        };
    }
}
#endif
