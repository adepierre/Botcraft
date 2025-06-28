#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/ItemAttributeModifiersDisplayData.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DefaultDisplay : public ItemAttributeModifiersDisplayData
        {

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
