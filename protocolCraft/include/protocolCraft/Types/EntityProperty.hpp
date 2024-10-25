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
        SERIALIZED_FIELD(Key, std::string);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(Key, Identifier);
#else
        SERIALIZED_FIELD(Key, VarInt);
#endif
        SERIALIZED_FIELD(Value, double);
        SERIALIZED_FIELD(Modifiers, std::vector<EntityModifierData>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
