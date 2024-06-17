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
            DECLARE_FIELDS(
                (std::vector<Filterable<std::string>>),
                (Pages)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Pages);
        };
    }
}
#endif
