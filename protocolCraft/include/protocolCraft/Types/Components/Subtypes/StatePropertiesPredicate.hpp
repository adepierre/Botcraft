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
            DECLARE_FIELDS(
                (std::vector<PropertyMatcher>),
                (Properties)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Properties);
        };
    }
}
#endif
