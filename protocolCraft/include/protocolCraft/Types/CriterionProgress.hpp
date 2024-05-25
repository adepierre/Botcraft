#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class CriterionProgress : public NetworkType
    {
        DECLARE_FIELDS_TYPES(std::optional<long long int>);
        DECLARE_FIELDS_NAMES(DateOfAchieving);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(DateOfAchieving);
    };
}
