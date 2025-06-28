#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

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
            SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Type, Internal::DiffType<ItemAttributeModifiersDisplayType, VarInt>);
            SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Data, std::shared_ptr<ItemAttributeModifiersDisplayData>);

            GETTER(Type);
            GETTER(Data);

            ItemAttributeModifiersDisplay& SetType(const ItemAttributeModifiersDisplayType type_);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
