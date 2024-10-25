#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"

namespace ProtocolCraft
{
    class RecipeDataSmithingTrim : public RecipeData
    {
        SERIALIZED_FIELD(Template, Ingredient);
        SERIALIZED_FIELD(Base, Ingredient);
        SERIALIZED_FIELD(Addition, Ingredient);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
