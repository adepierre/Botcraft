#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Filterable.hpp"

#include <string>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeWritableBookContent : public DataComponentType
        {
            SERIALIZED_FIELD(Pages, std::vector<Filterable<std::string>>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
