#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/ItemAttributeModifiersDisplay.hpp"

#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/DefaultDisplay.hpp"
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/HiddenDisplay.hpp"
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/OverrideDisplay.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        DEFINE_NETWORK_TYPE(DefaultDisplay);
        DEFINE_NETWORK_TYPE(HiddenDisplay);
        DEFINE_NETWORK_TYPE(OverrideDisplay);

        std::shared_ptr<ItemAttributeModifiersDisplayData> ItemAttributeModifiersDisplay::CreateItemAttributeModifiersDisplayData(const ItemAttributeModifiersDisplayType type)
        {
            switch (type)
            {
            case ItemAttributeModifiersDisplayType::Default:
                return std::make_shared<DefaultDisplay>();
            case ItemAttributeModifiersDisplayType::Hidden:
                return std::make_shared<HiddenDisplay>();
            case ItemAttributeModifiersDisplayType::Override:
                return std::make_shared<OverrideDisplay>();
            default:
                // This should not happen
                throw std::runtime_error("Unable to create ItemAttributeModifiersDisplayData with id: " + std::to_string(static_cast<int>(type)) + ".");
                return nullptr;
            }
        }

        DEFINE_NETWORK_TYPE(ItemAttributeModifiersDisplay);
    }
}
#endif
