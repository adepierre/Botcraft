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
            SERIALIZED_FIELD(Title, Filterable<std::string>);
            SERIALIZED_FIELD(Author, std::string);
            SERIALIZED_FIELD(Generation, VarInt);
            SERIALIZED_FIELD(Pages, std::vector<Filterable<Chat>>);
            SERIALIZED_FIELD(Resolved, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
