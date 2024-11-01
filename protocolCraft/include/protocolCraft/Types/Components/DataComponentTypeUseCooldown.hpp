#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeUseCooldown : public DataComponentType
        {
            SERIALIZED_FIELD(Seconds, float);
            SERIALIZED_FIELD(CooldownGroup, std::optional<Identifier>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
