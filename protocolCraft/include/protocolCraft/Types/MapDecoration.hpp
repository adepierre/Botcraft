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
        DECLARE_FIELDS(
            (char,       char, char),
            (RotAndType, X,    Z)
        );
#else
        DECLARE_FIELDS(
            (VarInt, char, char, char, std::optional<Chat>),
            (Type,   X,    Z,    Rot,  DisplayName)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        GETTER_SETTER(RotAndType);
#else
        GETTER_SETTER(Rot);
        GETTER_SETTER(DisplayName);
#endif
        GETTER_SETTER(X);
        GETTER_SETTER(Z);
    };
}
