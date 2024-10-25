#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSmithingTransform : public RecipeData
    {
        SERIALIZED_FIELD(Template, Ingredient);
        SERIALIZED_FIELD(Base, Ingredient);
        SERIALIZED_FIELD(Addition, Ingredient);
        SERIALIZED_FIELD(Result, Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
