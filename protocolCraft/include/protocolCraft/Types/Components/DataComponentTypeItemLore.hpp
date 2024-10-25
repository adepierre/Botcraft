#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeItemLore : public DataComponentType
        {
            SERIALIZED_FIELD(Lines, std::vector<Chat>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
