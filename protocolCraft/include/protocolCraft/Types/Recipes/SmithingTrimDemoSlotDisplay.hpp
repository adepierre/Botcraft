#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Components/Subtypes/TrimPattern.hpp"
#endif

namespace ProtocolCraft
{
    class SmithingTrimDemoSlotDisplay : public SlotDisplayData
    {
        SERIALIZED_FIELD(Base, SlotDisplay);
        SERIALIZED_FIELD(Material, SlotDisplay);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SERIALIZED_FIELD(Pattern, SlotDisplay);
#else
        SERIALIZED_FIELD(Pattern, Holder<Components::TrimPattern>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
