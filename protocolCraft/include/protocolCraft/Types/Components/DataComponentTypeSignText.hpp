#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDyeColor.hpp"

#include "protocolCraft/Types/Chat/Chat.hpp"

#include <array>
#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeSignText : public DataComponentType
        {
            SERIALIZED_FIELD(Messages, std::array<Chat, 4>);
            SERIALIZED_FIELD(FilteredMessagesForSerialization, std::optional<std::array<Chat, 4>>);
            SERIALIZED_FIELD(Color, DataComponentTypeDyeColor);
            SERIALIZED_FIELD(HasGlowingText, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
