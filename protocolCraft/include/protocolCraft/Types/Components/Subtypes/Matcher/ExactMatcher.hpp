#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/Subtypes/Matcher/ValueMatcher.hpp"

#include <string>

namespace ProtocolCraft
{
    namespace Components
    {
        class ExactMatcher : public ValueMatcher
        {
            DECLARE_FIELDS_TYPES(std::string);
            DECLARE_FIELDS_NAMES(Value);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Value);
        };
    }
}
#endif
