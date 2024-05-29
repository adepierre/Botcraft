#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"

namespace ProtocolCraft
{
    class RecipeDataSmithingTrim : public RecipeData
    {
        DECLARE_FIELDS_TYPES(Ingredient, Ingredient, Ingredient);
        DECLARE_FIELDS_NAMES(Template,   Base,       Addition);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Template);
        GETTER_SETTER(Base);
        GETTER_SETTER(Addition);
    };
}
#endif
