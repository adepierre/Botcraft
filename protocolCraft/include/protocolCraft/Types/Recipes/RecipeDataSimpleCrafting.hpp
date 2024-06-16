#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"

namespace ProtocolCraft
{
    class RecipeDataSimpleCrafting : public RecipeData
    {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_EMPTY;
#else
        DECLARE_FIELDS(
            (VarInt),
            (CookingBookCategory)
        );
        DECLARE_READ_WRITE_SERIALIZE;
#endif

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        GETTER_SETTER(CookingBookCategory);
#endif
    };
}
#endif
