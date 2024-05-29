#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Filterable.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

#include <string>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeWrittenBookContent : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(Filterable<std::string>, std::string, VarInt,     std::vector<Filterable<Chat>>, bool);
            DECLARE_FIELDS_NAMES(Title,                   Author,      Generation, Pages,                         Resolved);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Title);
            GETTER_SETTER(Author);
            GETTER_SETTER(Generation);
            GETTER_SETTER(Pages);
            GETTER_SETTER(Resolved);
        };
    }
}
#endif
