#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        enum class ItemAttributeModifiersDisplayType
        {
            None = -1,
            Default,
            Hidden,
            Override,
            NUM_DISPLAY_TYPES
        };

        class ItemAttributeModifiersDisplayData;

        class ItemAttributeModifiersDisplay : public NetworkType
        {
        private:
            static std::shared_ptr<ItemAttributeModifiersDisplayData> CreateItemAttributeModifiersDisplayData(const ItemAttributeModifiersDisplayType type);

            SERIALIZED_DYNAMIC_FIELD(ItemAttributeModifiersDisplay, Type, Data, ItemAttributeModifiersDisplayData, ItemAttributeModifiersDisplay::CreateItemAttributeModifiersDisplayData, Internal::DiffType<ItemAttributeModifiersDisplayType, VarInt>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
