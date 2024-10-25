#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include <map>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBlockItemStateProperties : public DataComponentType
        {
            SERIALIZED_FIELD(Properties, std::map<std::string, std::string>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
