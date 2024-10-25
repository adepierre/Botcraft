#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class CriterionProgress : public NetworkType
    {
        SERIALIZED_FIELD(DateOfAchieving, std::optional<long long int>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
