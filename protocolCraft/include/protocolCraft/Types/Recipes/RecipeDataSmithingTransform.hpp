#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSmithingTransform : public RecipeData
    {
        DECLARE_FIELDS_TYPES(Ingredient, Ingredient, Ingredient, Slot);
        DECLARE_FIELDS_NAMES(Template,   Base,       Addition,   Result);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Template);
        GETTER_SETTER(Base);
        GETTER_SETTER(Addition);
        GETTER_SETTER(Result);
    };
}
#endif
