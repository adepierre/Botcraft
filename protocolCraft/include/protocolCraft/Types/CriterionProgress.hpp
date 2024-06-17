#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class CriterionProgress : public NetworkType
    {
        DECLARE_FIELDS(
            (std::optional<long long int>),
            (DateOfAchieving)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(DateOfAchieving);
    };
}
