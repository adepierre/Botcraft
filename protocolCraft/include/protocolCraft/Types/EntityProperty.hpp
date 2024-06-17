#pragma once

#include <vector>
#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/EntityModifierData.hpp"
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class EntityProperty : public NetworkType
    {
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (std::string, double, std::vector<EntityModifierData>),
            (Key,         Value,  Modifiers)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (Identifier,  double, std::vector<EntityModifierData>),
            (Key,         Value,  Modifiers)
        );
#else
        DECLARE_FIELDS(
            (VarInt, double, std::vector<EntityModifierData>),
            (Key,    Value,  Modifiers)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Key);
        GETTER_SETTER(Value);
        GETTER_SETTER(Modifiers);
    };
}
