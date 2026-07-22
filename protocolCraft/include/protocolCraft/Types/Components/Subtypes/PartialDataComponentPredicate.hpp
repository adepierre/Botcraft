#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"


namespace ProtocolCraft
{
    namespace Components
    {
        class PartialDataComponentPredicate : public NetworkType
        {
            SERIALIZED_FIELD(Type, Either<VarInt, VarInt>); // either a DATA_COMPONENT_PREDICATE_TYPE or a DATA_COMPONENT_TYPE but we need to read the either boolean
            SERIALIZED_FIELD(Value, NBT::UnnamedValue);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
