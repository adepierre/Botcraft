#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class EntityModifierData : public NetworkType
    {
        DECLARE_FIELDS_TYPES(UUID, double, char);
        DECLARE_FIELDS_NAMES(Uuid, Amount, Operation);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
        GETTER_SETTER(Amount);
        GETTER_SETTER(Operation);
    };
}
