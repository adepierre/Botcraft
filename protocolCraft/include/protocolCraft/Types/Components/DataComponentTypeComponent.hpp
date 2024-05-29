#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeComponent : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(Chat);
            DECLARE_FIELDS_NAMES(Component);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Component);
        };
    }
}
#endif
