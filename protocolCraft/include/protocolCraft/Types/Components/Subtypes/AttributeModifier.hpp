#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class AttributeModifier : public NetworkType
        {
            SERIALIZED_FIELD(Id, UUID);
            SERIALIZED_FIELD(Name, std::string);
            SERIALIZED_FIELD(Amount, double);
            SERIALIZED_FIELD(Operation, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
