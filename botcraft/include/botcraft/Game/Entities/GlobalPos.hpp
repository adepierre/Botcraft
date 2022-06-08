#if PROTOCOL_VERSION > 758
#pragma once

#include <string>

#include "botcraft/Game/Vector3.hpp"

#include "protocolCraft/Types/Identifier.hpp"

namespace Botcraft
{
    struct GlobalPos
    {
        ProtocolCraft::Identifier dimension;
        Position pos;
    };
}
#endif
