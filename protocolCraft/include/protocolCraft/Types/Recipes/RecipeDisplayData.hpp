#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class RecipeDisplayData : public NetworkType
    {
    public:
        virtual ~RecipeDisplayData() {};
    };
}
#endif
