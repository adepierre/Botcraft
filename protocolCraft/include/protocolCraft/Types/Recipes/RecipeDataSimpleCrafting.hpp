#if PROTOCOL_VERSION > 347 /* > 1.12.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"

namespace ProtocolCraft
{
    class RecipeDataSimpleCrafting : public RecipeData
    {
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        SERIALIZED_FIELD(CookingBookCategory, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
