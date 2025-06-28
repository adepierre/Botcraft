#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/AttributeModifier.hpp"
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/ItemAttributeModifiersDisplay.hpp"
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class ItemAttributeModifiersEntry : public NetworkType
        {
            SERIALIZED_FIELD(Attribute, VarInt);
            SERIALIZED_FIELD(Modifier, AttributeModifier);
            SERIALIZED_FIELD(Slot, VarInt);
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
            SERIALIZED_FIELD(Display, ProtocolCraft::Components::ItemAttributeModifiersDisplay);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
