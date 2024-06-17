#pragma once

#include <map>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/CriterionProgress.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class AdvancementProgress : public NetworkType
    {
    public:
        DECLARE_FIELDS(
            (std::map<Identifier, CriterionProgress>),
            (Criteria)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Criteria);
    };
}
