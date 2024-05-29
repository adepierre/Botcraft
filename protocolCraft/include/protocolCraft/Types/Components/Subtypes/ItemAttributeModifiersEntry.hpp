#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/AttributeModifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class ItemAttributeModifiersEntry : public NetworkType
        {
            DECLARE_FIELDS_TYPES(VarInt,    AttributeModifier, VarInt);
            DECLARE_FIELDS_NAMES(Attribute, Modifier,          Slot);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Attribute);
            GETTER_SETTER(Modifier);
            GETTER_SETTER(Slot);
        };
    }
}
#endif
