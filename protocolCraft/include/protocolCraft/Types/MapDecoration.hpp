#pragma once

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION > 363 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class MapDecoration : public NetworkType
    {
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(RotAndType, char);
#else
        SERIALIZED_FIELD(Type, VarInt);
#endif
        SERIALIZED_FIELD(X, char);
        SERIALIZED_FIELD(Z, char);
#if PROTOCOL_VERSION > 363 /* > 1.12.2 */
        SERIALIZED_FIELD(Rot, char);
        SERIALIZED_FIELD(DisplayName, std::optional<Chat>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
