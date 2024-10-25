#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/PropertyMatcher.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class StatePropertiesPredicate : public NetworkType
        {
            SERIALIZED_FIELD(Properties, std::vector<PropertyMatcher>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
