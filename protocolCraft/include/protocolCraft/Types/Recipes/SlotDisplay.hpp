#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"

#include <memory>

namespace ProtocolCraft
{
    enum class SlotDisplayDataType
    {
        None = -1,
        Empty,
        AnyFuel,
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        WithAnyPotion,
        OnlyWithComponent,
#endif
        Item,
        ItemStack,
        Tag,
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        DyedSlotDemo,
#endif
        SmithingTrim,
        WithRemainder,
        Composite,
        NUM_SLOT_DISPLAY_DATA_TYPES
    };

    class SlotDisplayData;

    class SlotDisplay : public NetworkType
    {
    private:
        static std::shared_ptr<SlotDisplayData> CreateSlotDisplayData(const SlotDisplayDataType type);

        SERIALIZED_DYNAMIC_FIELD(SlotDisplay, Type, Data, SlotDisplayData, SlotDisplay::CreateSlotDisplayData, Internal::DiffType<SlotDisplayDataType, VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
