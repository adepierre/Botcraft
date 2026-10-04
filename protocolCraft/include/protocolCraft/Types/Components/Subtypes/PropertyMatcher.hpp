#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Components/Subtypes/Matcher/ExactMatcher.hpp"
#include "protocolCraft/Types/Components/Subtypes/Matcher/RangedMatcher.hpp"

#include <string>
#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class PropertyMatcher : public NetworkType
        {
            SERIALIZED_FIELD(Name, std::string);
            SERIALIZED_FIELD(Value, Either<ProtocolCraft::Components::ExactMatcher, ProtocolCraft::Components::RangedMatcher>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
