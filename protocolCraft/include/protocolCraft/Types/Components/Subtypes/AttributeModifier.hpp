#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class AttributeModifier : public NetworkType
        {
#if PROTOCOL_VERSION < 767 /* < 1.21 */
            SERIALIZED_FIELD(Id, UUID);
            SERIALIZED_FIELD(Name, std::string);
#else
            SERIALIZED_FIELD(Id, Identifier);
#endif
            SERIALIZED_FIELD(Amount, double);
            SERIALIZED_FIELD(Operation, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
