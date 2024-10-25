#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class NumberFormat : public NetworkType
    {
        DEFINE_CONDITION(HasFormat, GetType() != 0);

        SERIALIZED_FIELD(Type, VarInt);
        SERIALIZED_FIELD(Format, Internal::Conditioned<Chat, &NumberFormat::HasFormat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
