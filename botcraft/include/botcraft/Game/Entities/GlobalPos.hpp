#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once
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
