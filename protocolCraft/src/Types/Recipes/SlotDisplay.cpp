#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

#include "protocolCraft/Types/Recipes/CompositeSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/ItemSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/ItemStackSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplayDataEmpty.hpp"
#include "protocolCraft/Types/Recipes/SmithingTrimDemoSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/TagSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/WithRemainderSlotDisplay.hpp"
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
#include "protocolCraft/Types/Recipes/DyedSlotDemoDisplayData.hpp"
#include "protocolCraft/Types/Recipes/OnlyWithComponentSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/WithAnyPotionSlotDisplay.hpp"
#endif

#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

namespace ProtocolCraft
{
    DEFINE_NETWORK_TYPE(CompositeSlotDisplay);
    DEFINE_NETWORK_TYPE(ItemSlotDisplay);
    DEFINE_NETWORK_TYPE(ItemStackSlotDisplay);
    DEFINE_NETWORK_TYPE(SlotDisplayDataEmpty);
    DEFINE_NETWORK_TYPE(SmithingTrimDemoSlotDisplay);
    DEFINE_NETWORK_TYPE(TagSlotDisplay);
    DEFINE_NETWORK_TYPE(WithRemainderSlotDisplay);
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    DEFINE_NETWORK_TYPE(DyedSlotDemoDisplayData);
    DEFINE_NETWORK_TYPE(OnlyWithComponentSlotDisplay);
    DEFINE_NETWORK_TYPE(WithAnyPotionSlotDisplay);
#endif


    std::shared_ptr<SlotDisplayData> SlotDisplay::CreateSlotDisplayData(const SlotDisplayDataType type)
    {
        switch (type)
        {
        case SlotDisplayDataType::Empty:
        case SlotDisplayDataType::AnyFuel:
            return std::make_shared<SlotDisplayDataEmpty>();
        case SlotDisplayDataType::Item:
            return std::make_shared<ItemSlotDisplay>();
        case SlotDisplayDataType::ItemStack:
            return std::make_shared<ItemStackSlotDisplay>();
        case SlotDisplayDataType::Tag:
            return std::make_shared<TagSlotDisplay>();
        case SlotDisplayDataType::SmithingTrim:
            return std::make_shared<SmithingTrimDemoSlotDisplay>();
        case SlotDisplayDataType::WithRemainder:
            return std::make_shared<WithRemainderSlotDisplay>();
        case SlotDisplayDataType::Composite:
            return std::make_shared<CompositeSlotDisplay>();
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        case SlotDisplayDataType::WithAnyPotion:
            return std::make_shared<WithAnyPotionSlotDisplay>();
        case SlotDisplayDataType::OnlyWithComponent:
            return std::make_shared<OnlyWithComponentSlotDisplay>();
        case SlotDisplayDataType::DyedSlotDemo:
            return std::make_shared<DyedSlotDemoDisplayData>();
#endif
        default:
            // This should not happen
            throw std::runtime_error("Unable to create SlotDisplaysData with id: " + std::to_string(static_cast<int>(type)) + ".");
        }
    }

    DEFINE_NETWORK_TYPE(SlotDisplay);
}
#endif
