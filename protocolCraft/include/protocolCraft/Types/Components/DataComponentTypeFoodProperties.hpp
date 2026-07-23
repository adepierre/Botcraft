#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "protocolCraft/Types/Components/Subtypes/PossibleEffect.hpp"
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Types/Item/Slot.hpp"

#include <optional>
#endif
#include <vector>
#endif


namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeFoodProperties : public DataComponentType
        {
            SERIALIZED_FIELD(Nutrition, VarInt);
            SERIALIZED_FIELD(Saturation, float);
            SERIALIZED_FIELD(CanAlwaysEat, bool);
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            SERIALIZED_FIELD(EatSeconds, float);
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
            SERIALIZED_FIELD(UsingConvertsTo, std::optional<Slot>);
#endif
            SERIALIZED_FIELD(Effects, std::vector<PossibleEffect>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
