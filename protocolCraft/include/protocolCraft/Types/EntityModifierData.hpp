#pragma once

#include "protocolCraft/NetworkType.hpp"

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class EntityModifierData : public NetworkType
    {

#if PROTOCOL_VERSION < 767 /* < 1.20.6 */
        SERIALIZED_FIELD(Uuid, UUID);
#else
        SERIALIZED_FIELD(Id, Identifier);
#endif
        SERIALIZED_FIELD(Amount, double);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(Operation, char);
#else
        SERIALIZED_FIELD(Operation, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
