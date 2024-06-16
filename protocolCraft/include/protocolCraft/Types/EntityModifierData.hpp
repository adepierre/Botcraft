#pragma once

#include "protocolCraft/NetworkType.hpp"

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class EntityModifierData : public NetworkType
    {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_TYPES(UUID, double, char);
        DECLARE_FIELDS_NAMES(Uuid, Amount, Operation);
#elif PROTOCOL_VERSION < 767 /* < 1.20.6 */
        DECLARE_FIELDS_TYPES(UUID, double,   VarInt);
        DECLARE_FIELDS_NAMES(Uuid,   Amount, Operation);
#else
        DECLARE_FIELDS_TYPES(Identifier, double, VarInt);
        DECLARE_FIELDS_NAMES(Id,         Amount, Operation);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 767 /* < 1.21 */
        GETTER_SETTER(Uuid);
#else
        GETTER_SETTER(Id);
#endif
        GETTER_SETTER(Amount);
        GETTER_SETTER(Operation);
    };
}
