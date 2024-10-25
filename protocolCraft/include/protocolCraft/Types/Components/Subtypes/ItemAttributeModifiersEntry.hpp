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
            SERIALIZED_FIELD(Attribute, VarInt);
            SERIALIZED_FIELD(Modifier, AttributeModifier);
            SERIALIZED_FIELD(Slot, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
