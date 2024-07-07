#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyInteger : public BrigadierProperty
    {
        DECLARE_CONDITION(Flags1, GetFlags() & 0x01);
        DECLARE_CONDITION(Flags2, GetFlags() & 0x02);

        DECLARE_FIELDS(
            (char,  Internal::Conditioned<int, &BrigadierPropertyInteger::Flags1>, Internal::Conditioned<int, &BrigadierPropertyInteger::Flags2>),
            (Flags, Min,                                                           Max)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Flags);
        GETTER_SETTER(Min);
        GETTER_SETTER(Max);
    };
}
#endif
