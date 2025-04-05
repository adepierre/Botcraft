#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class TestInstanceBlockEntityData : public NetworkType
    {
        SERIALIZED_FIELD(Test, std::optional<std::string>);
        SERIALIZED_FIELD(Size, std::array<VarInt, 3>);
        SERIALIZED_FIELD(Rotation, VarInt);
        SERIALIZED_FIELD(IgnoreEntities, bool);
        SERIALIZED_FIELD(Status, VarInt);
        SERIALIZED_FIELD(ErrorMessage, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
