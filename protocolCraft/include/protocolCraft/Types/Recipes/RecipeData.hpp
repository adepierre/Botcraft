#if PROTOCOL_VERSION > 347 /* > 1.12.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

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
