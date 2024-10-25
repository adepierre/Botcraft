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
        SERIALIZED_FIELD(Criteria, std::map<Identifier, CriterionProgress>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
