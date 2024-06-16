#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class GlobalPos : public NetworkType
    {
        DECLARE_FIELDS(
            (Identifier, NetworkPosition),
            (Dimension,  Pos)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Dimension);
        GETTER_SETTER(Pos);
    };
}
#endif
