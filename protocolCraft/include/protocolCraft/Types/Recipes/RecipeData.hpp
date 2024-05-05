#pragma once

#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class RecipeData : public NetworkType
    {
    public:
        virtual ~RecipeData() override {};
    };
}
#endif
