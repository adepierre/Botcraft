#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class NumberFormat : public NetworkType
    {
        DECLARE_CONDITION(HasFormat, GetType() != 0);

        DECLARE_FIELDS(
            (VarInt, Internal::Conditioned<Chat, &NumberFormat::HasFormat>),
            (Type,   Format)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Type);
        GETTER_SETTER(Format);
    };
} // ProtocolCraft
#endif
