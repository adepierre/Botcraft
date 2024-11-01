#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Recipes/RecipeDisplayEntry.hpp"

namespace ProtocolCraft
{
    class RecipeBookAddEntry : public NetworkType
    {
        SERIALIZED_FIELD(Contents, RecipeDisplayEntry);
        SERIALIZED_FIELD(Flags, unsigned char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
