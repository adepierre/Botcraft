#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class PaintingVariant : public NetworkType
        {
            SERIALIZED_FIELD(Width, VarInt);
            SERIALIZED_FIELD(Height, VarInt);
            SERIALIZED_FIELD(AssetId, Identifier);
            SERIALIZED_FIELD(Title, std::optional<Chat>);
            SERIALIZED_FIELD(Author, std::optional<Chat>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
