#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/ItemAttributeModifiersDisplayData.hpp"

#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class OverrideDisplay : public ItemAttributeModifiersDisplayData
        {
            SERIALIZED_FIELD(Component, Chat);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
