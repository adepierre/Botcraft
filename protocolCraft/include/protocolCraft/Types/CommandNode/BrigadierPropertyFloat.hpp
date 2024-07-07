#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyFloat : public BrigadierProperty
    {
        DECLARE_CONDITION(Flags1, GetFlags() & 0x01);
        DECLARE_CONDITION(Flags2, GetFlags() & 0x02);

        DECLARE_FIELDS(
            (char,  Internal::Conditioned<float, &BrigadierPropertyFloat::Flags1>, Internal::Conditioned<float, &BrigadierPropertyFloat::Flags2>),
            (Flags, Min,                                                           Max)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Flags);
        GETTER_SETTER(Min);
        GETTER_SETTER(Max);
    };
}
#endif
