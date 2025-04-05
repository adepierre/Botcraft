#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DamageReduction : public NetworkType
        {
            SERIALIZED_FIELD(HorizontalBlockingAngle, float);
            SERIALIZED_FIELD(Type, std::optional<HolderSet>);
            SERIALIZED_FIELD(Base, float);
            SERIALIZED_FIELD(Factor, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
